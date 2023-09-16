/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
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


struct Info **initialize_mgp(struct Group *g,int *gids_arr, int n);
/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(struct Group *g){
    int i;
    struct Group *tmp;

    for(i = 0; i < MG; i++) {
        tmp = malloc(sizeof(struct Group));
        tmp->gId = i;
        tmp->ggsub = L_Initialize();
        tmp->gfirst = DL_Initialize();
        tmp->glast = DL_Initialize();

        tmp->glast = tmp->gfirst;
        g[i] = *tmp;
    }
    return EXIT_SUCCESS;
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
 * Updates every Subscriber of group's sub list,
 * so that
 * @param g Group containing Subscription List
 * @param s
 */
void updateSGP(struct Group g, struct SubInfo **s) {
    struct Subscription *sub_list = g.ggsub;
    struct Info **curr_sgp;

    while(sub_list) { /* traverse each subscription */
        curr_sgp = SL_getSgp(*s,sub_list->Sid); /* get sgp list of curr subscriber */
        if(!curr_sgp) {
            return; /* if sub list is empty or sub does not exist  */
        }
        curr_sgp[g.gId] = g.gfirst;  /* point sgp of curr sub to new info node(g.gfirst) */
        sub_list = sub_list->next;
    }

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
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr, struct Group *g, struct SubInfo **s){
    int i = 0;
    int insert_success;
    int val;

    while(gids_arr[i] != -1 && i < size_of_gids_arr) { /* for each group of new info*/
        val = gids_arr[i];
        if(val >= MG) { /* check if index is valid */
            fprintf(stderr, "Index must be in range [%d,%d]",0,MG);
            return EXIT_FAILURE;
        }

        struct Info *n = DL_CreateNode(iId,iTM,gids_arr); /* create a node with specified params */
        insert_success = DL_Insert(&(g[val]).gfirst,n); /* insert it in current group list */

        if(insert_success == 1) { /* list had at least 1 elem before */
            g[val].glast = DL_Lookup_Last(g[val].glast);
        } else if(insert_success == 2) { /* new_node is first elem of list*/
            updateSGP(g[val],s); /* update all subs of g[val] to point to new_node */
            g[val].glast = g[val].gfirst; /* update glast to point to last node */
        } else {
            fprintf(stderr,"\nnode with id %d already exists in index %d\n",n->iID,val);
            return EXIT_FAILURE;
        }

        i++;
    }
    Print_Group_Info(g,MG,gids_arr,size_of_gids_arr);
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
    int i = 0;
    int val;


    struct Info **mgp = initialize_mgp(g,gids_arr,MG);
    struct Subscription *tmp_sub;

    /* make sgp point to corresponding groups */
    struct SubInfo *n = SL_CreateNode(sId,sTM,mgp);
    SL_Insert(s,n);

    while(gids_arr[i] != -1) {
        tmp_sub = L_Create_Node(sId);
        val = gids_arr[i];

        if(val >= MG) { /* check if index is valid */
            fprintf(stderr, "Index must be in range [%d,%d]",0,MG);
            i++;
            continue;
        }

        L_Insert(&(g[val]).ggsub,tmp_sub);
        i++;
    }
    Print_Group_Sub(g,*s,MG,gids_arr,size_of_gids_arr);
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(struct SubInfo  *s,int sId){
    int i;
    struct Info **tmp = SL_getSgp(s,sId);

    /* if sub list is empty or sub does not exist  */
    if(!tmp) {
        return EXIT_FAILURE;
    }

    for(i = 0; i < MG; i++) {
        if(tmp[i] != 1) {
            fprintf(stderr,"GROUPID = <%d>,",i);
            if(tmp[i]) {
                tmp[i] = DL_Traverse_Print(tmp[i]);
            } else {
                fprintf(stderr, "INFOLIST = <>");
            }
            fprintf(stderr,",NEWSGP = ");
            if(tmp[i] != 1 && tmp[i] != NULL) {
                fprintf(stderr,"<%d>",tmp[i]->iID);
            }
            fprintf(stderr,"\n");
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
int Delete_Subscriber(struct Group *g, struct SubInfo **s,int sId){
    int i = 0;
    struct Info **tmp = SL_getSgp(*s,sId);

    /* if sub list is empty or sub does not exist  */
    if(!tmp) {
        return EXIT_FAILURE;
    }


    /* for each group */
    while(i < MG) {
        if(tmp[i] != 1) { /* if sub is registered in group[i] */
            L_Delete(&g[i].ggsub,sId);
        }
        i++;
    }


    /* delete sub from subscriber list  */
    SL_Delete(s,sId);

    return EXIT_SUCCESS;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(struct Group *g, struct SubInfo *s, int n){
    int i;

    for(i = 0; i < n; i++) {
        fprintf(stderr,"GROUPID = <%d>,",g[i].gId);
        DL_Print(g[i].gfirst);
        fprintf(stderr,",");
        L_PrintList(g[i].ggsub);
        fprintf(stderr,"\n");
    }
    SL_Print(s);
    SL_Print_Indiv(s,n);

    fprintf(stderr,"NO_GROUPS = %d,",n);
    fprintf(stderr,"NO_SUBSCRIBERS = %d\n", SL_len(s));

    return EXIT_SUCCESS;
}

void Print_Group_Info(struct Group *g, int n, int* gids_arr, int gids_arr_sz) {
    int i = 0;
    int val;

    while(gids_arr[i] != -1 && i < gids_arr_sz) {
        val = gids_arr[i];
        fprintf(stderr, "GROUPID = <%d>,",g[val].gId);
        DL_Print(g[val].gfirst);
        fprintf(stderr,"\n");
        i++;
    }

}

void Print_Group_Sub(struct Group *g,struct SubInfo *s, int n, int* gids_arr,int size_of_gids_arr) {
    int i = 0;
    int val;
    SL_Print(s);

    while(i < size_of_gids_arr && gids_arr[i] != -1 && gids_arr[i] < MG) {
        val = gids_arr[i];
        fprintf(stderr,"GROUPID = <%d>,",g[val].gId);
        L_PrintList(g[val].ggsub);
        fprintf(stderr,"\n");
        i++;
    }
}

struct Info **initialize_mgp(struct Group *g,int *gids_arr, int n) {
    int i;
    int val;
    struct Info **tmp = malloc(64*sizeof(struct Info));

    /* set all pointers to 1  */
    for(i = 0; i < n; i++) {
        tmp[i] = DL_Initialize();
        tmp[i] = 1;
    }

    i = 0;
    while(i < MG && gids_arr[i] != -1 && gids_arr[i] < MG) {
        val = gids_arr[i];

        /* if info list of G[val] is empty */
        if(g[val].gfirst->iID == -1) {
            tmp[val] = NULL;
            i++;
            continue;
        }
        tmp[val] = g[val].gfirst;
        i++;
    }

    return tmp;
}

