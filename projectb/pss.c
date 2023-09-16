/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "pss.h"


struct Info *popNodesUntil(int tm, struct Info **root);

void delNodeUntilUtil(int tm, struct Info **root, struct Info *nodes);

int updateTree(struct TreeInfo **tree, struct Info *Tree);

void Print_Group_Info(struct Group *g, int *gids_arr, int gids_arr_sz);

void Print_Group_Sub(struct  Group *g, struct SubInfo **s, int *gids_arr, int gids_arr_sz);

void Print_Group_Prune(struct Group *g, struct SubInfo **s, int includeSubList);
/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of the hash table.
 * @param p Prime number for the universal hash functions.
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p, struct Group *g, struct SubInfo **t){
    int i;


    for(i = 0; i < MG; i++) {
        g[i].gId = i;
        g[i].gr = BST_Initialize();
        g[i].gsub = L_Initialize();
    }


    return EXIT_SUCCESS;
}

void getNodeUntilUtil(int tm, struct Info *root, struct Info **tmp) {

    if(!root) {
        return;
    }

    getNodeUntilUtil(tm,root->ilc,tmp);

    if(root->itm < tm) {
        struct Info *tmp_node = BST_newNode(root->iId,root->itm,root->igp);
        BST_Insert(tmp,tmp_node);
    }

    getNodeUntilUtil(tm,root->irc,tmp);

}

struct Info *popNodesUntil(int tm, struct Info **root) {
    struct Info *tmp = BST_Initialize();

    getNodeUntilUtil(tm,*root,&tmp);
    delNodeUntilUtil(tm,root,tmp);

    return tmp;
}


struct TreeInfo *Traverse_Print_Tree(struct TreeInfo *sgpTree);

void Print_Group_Delete(struct Group *g, struct SubInfo **s, int *gids_arr);

void delNodeUntilUtil(int tm, struct Info **root, struct Info *nodes) {

    if(!nodes) {
        return;
    }

    delNodeUntilUtil(tm,root,nodes->ilc);

    BST_Delete(root,nodes->iId);

    delNodeUntilUtil(tm,root,nodes->irc);

}

struct TreeInfo *Traverse_Print_Tree(struct TreeInfo *sgpTree) {

    fprintf(stderr,"TREELIST = <");
    if(!sgpTree) {
        fprintf(stderr,">");
        return sgpTree;
    }


    while(sgpTree->next) {
        fprintf(stderr,"%d",sgpTree->tId);
        if(sgpTree->next) {
            fprintf(stderr,",");
        }
        sgpTree = sgpTree->next;
    }
    fprintf(stderr,"%d>",sgpTree->tId);

    return sgpTree;
}


/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int  *gids_arr,int size_of_gids_arr, struct Group *g){
    int i = 0;
    int insert_success;
    int val;

    while(gids_arr[i] != -1) {// for each group of new info
        val = gids_arr[i];

        if(val >= MG) { /* check if index is valid */
            fprintf(stderr, "Index must be in range [%d,%d]",0,MG);
            return EXIT_FAILURE;
        }

        struct Info *n = BST_newNode(iId,iTM,gids_arr);
        insert_success = BST_Insert(&(g[val]).gr,n);

        i++;
    }
    Print_Group_Info(g,gids_arr,size_of_gids_arr);
    return EXIT_SUCCESS;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr, struct Group *g, struct SubInfo **s){


    //create new subscriber
    struct SubInfo *n = HT_newNode(sId,sTM,gids_arr);
    HT_Insert(s,n); //add them to hash table

    struct Subscription *tmp_sub;

    int i = 0;
    int val;
    while(gids_arr[i] != -1) { /* add them to subscription list of each group in gids_arr */
        tmp_sub = L_Create_Node(sId);

        val = gids_arr[i];
        if(val >= MG) { /* check if index is valid */
            fprintf(stderr, "Index must be in range [%d,%d]",0,MG);
            i++;
            continue;
        }
        L_Insert(&(g[val]).gsub,tmp_sub);

        i++;
    }
    Print_Group_Sub(g,s,gids_arr,size_of_gids_arr);
    return EXIT_SUCCESS;
}
/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(int tm, struct Group *g, struct SubInfo **s){

    //for each group
    for(int i = 0; i < MG; i++) {

        struct SubInfo *sub;

        //pop all nodes with timestamp < tm from info tree, to tree_to_be_added
        struct Info *tree_to_be_added = popNodesUntil(tm,&g[i].gr);

        struct Subscription *cur_subList = g[i].gsub; // update all subs in current sub-list

        while(cur_subList) { //for each subscription
            int cur_sub_id = cur_subList->Sid;

            int status = updateTree(&HT_Lookup(s,cur_sub_id)->tgp[i],tree_to_be_added); //update subscriber

            if(status == 1) { //tgp tree was empty before
                //update sgp to point to first leaf node of tgp

                sub = HT_Lookup(s,cur_sub_id);
                sub->sgp[i] = LO_BST_Min(sub->tgp[i]);
            } else if(status == 0) {
                sub = HT_Lookup(s,cur_sub_id);
                sub->sgp[i] = LO_BST_Lookup(sub->tgp[i],sub->sgp[i]->ttm);
            }

            cur_subList = cur_subList->next;
        }

    }
    Print_Group_Prune(g,s,0);
    return EXIT_SUCCESS;
}

int  updateTree(struct TreeInfo **dest_tree, struct Info *src_tree) {

    if(!src_tree || (*dest_tree) == 1) {
        return -1;
    }

    int return_val = (*dest_tree) == NULL;
    updateTree(dest_tree,src_tree->ilc);

    struct TreeInfo *new_node = LO_BST_newNode(src_tree->iId,src_tree->itm);
    LO_BST_Insert(dest_tree,new_node);

    updateTree(dest_tree,src_tree->irc);

    return return_val;
}

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId, struct SubInfo **s){

    struct SubInfo *sub = HT_Lookup(s,sId);

    if(!sub) {
        fprintf(stderr,"Subscriber does not exist\n");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < MG; i++) {
        if(sub->sgp[i] != 1) {
            fprintf(stderr,"GROUPID = <%d>,",i);
            sub->sgp[i] = Traverse_Print_Tree(sub->sgp[i]);

            fprintf(stderr,",NEWSGP = <");
            if(sub->sgp[i]) {
                fprintf(stderr,"%d",sub->sgp[i]->tId);
            }
            fprintf(stderr,">\n");
        }
    }

    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId, struct Group *g, struct SubInfo **s){
    int includes[MG];
    for(int i = 0; i < MG; i++) {
        includes[i] = 0;
    }

    if(!HT_Lookup(s,sId)) {
        fprintf(stderr,"Subscriber does not exist");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < MG; i++) {
        includes[i] = L_Delete(&g[i].gsub,sId);
    }

    HT_Delete(s,sId);

    Print_Group_Delete(g,s,includes);

    return EXIT_SUCCESS;
}



/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(struct Group *g, struct SubInfo **s){

    Print_Group_Prune(g,s,1);

    fprintf(stderr,"\n\nNO_GROUPS = <%d>",MG);
    fprintf(stderr,",NO_SUBSCRIBERS = <%d>\n", HT_count(s));

    return EXIT_SUCCESS;
}

void Print_Group_Delete(struct Group *g, struct SubInfo **s, int *gids_arr) {

    HT_Print(s);

    for(int i = 0; i < MG; i++) {
        if(gids_arr[i]) {
            fprintf(stderr, "GROUPID = <%d>,",i);
            L_PrintList(g[i].gsub);
            fprintf(stderr,"\n");
        }
    }
}

void Print_Group_Info(struct Group *g, int *gids_arr, int gids_arr_sz) {
    int i = 0;
    int val;

    while(i < gids_arr_sz && gids_arr[i] != -1 && gids_arr[i] < MG) {
        val = gids_arr[i];
        fprintf(stderr,"GROUPID = <%d>,",g[val].gId);
        BST_Print(g[val].gr);
        fprintf(stderr,"\n");
        i++;
    }
}

void Print_Group_Sub(struct Group *g, struct SubInfo **s, int *gids_arr, int gids_arr_sz) {
    int i = 0;
    int val;
    HT_Print(s);

    while(i < gids_arr_sz && gids_arr[i] != -1 && gids_arr[i] < MG) {
        val = gids_arr[i];
        fprintf(stderr,"GROUPID = <%d>,",g[val].gId);
        L_PrintList(g[val].gsub);
        fprintf(stderr,"\n");
        i++;
    }
}

void Print_Group_Prune(struct Group *g, struct SubInfo **s, int includeSubList) {

    for(int i = 0; i < MG; i++) {
        fprintf(stderr,"GROUPID = <%d>,",g[i].gId);
        BST_Print(g[i].gr);
        L_PrintList(g[i].gsub);
        fprintf(stderr,"\n");
    }

    if(includeSubList) {
        HT_Print(s);
        fprintf(stderr,"\n");
    }

    int m = HT_getM();
    struct SubInfo *tmp;
    for(int i = 0; i < m; i++) {
        tmp = s[i];
        while(tmp) {
            fprintf(stderr,"SUBSCRIBERID = <%d>,",tmp->sId);
            HT_PrintTgp(tmp);
            tmp = tmp->snext;
        }
    }

}