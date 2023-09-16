#include <stdio.h>
#include "LO_TreeInfo.h"


int LO_BST_isLeaf(struct TreeInfo *n);
struct TreeInfo *LO_BST_Min(struct TreeInfo *root);


struct TreeInfo *LO_BST_Initialize() {
    return NULL;
}

struct TreeInfo *LO_BST_newNode(int _tId, int _ttm) {
    struct TreeInfo *tmp = malloc(sizeof(struct TreeInfo));
    assert(tmp);

    tmp->tId = _tId;
    tmp->ttm = _ttm;
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->tlc = NULL;
    tmp->trc = NULL;
    tmp->tp = NULL;

    return tmp;
}

int LO_BST_Insert(struct TreeInfo **root, struct TreeInfo *new_node) {
    struct TreeInfo *n;

    if(!(*root)) { //if tree is empty
        *root = new_node;
        return -1;
    }

    //if tree has only one node
    if(LO_BST_isLeaf(*root)) { //if root node is a leaf(only node in tree)
        if((*root)->ttm > new_node->ttm) {
            struct TreeInfo *new_rc = LO_BST_newNode((*root)->tId,(*root)->ttm); //create new right child with root val
            struct TreeInfo *new_par = LO_BST_newNode(new_node->tId,new_node->ttm); //create new parent with new_node val

            *root = new_par;

            new_par->tlc = new_node;
            new_par->trc = new_rc;

            new_node->tp = new_par;
            new_rc->tp = new_par;

            new_node->next = new_rc;
            new_rc->prev = new_node;

        } else {
            struct TreeInfo *new_lc = LO_BST_newNode((*root)->tId,(*root)->ttm); //create new left child with root val
            struct TreeInfo *new_par = LO_BST_newNode((*root)->tId,(*root)->ttm); //create new parent with root val

            *root = new_par;

            new_par->tlc = new_lc;
            new_par->trc = new_node;

            new_lc->tp = new_par;
            new_node->tp = new_par;

            new_lc->next = new_node;
            new_node->prev = new_lc;
        }
        return 1;
    }

    n = *root;

    while(!LO_BST_isLeaf(n)) {
        if(n->ttm < new_node->ttm) {
            n = n->trc;
        } else {
            n = n->tlc;
        }
    }

    if(n->ttm == new_node->ttm) {return -1;} //if new_node->ttm already exists return failure

    if(n->ttm > new_node->ttm) {
        struct TreeInfo *new_par = LO_BST_newNode(new_node->tId,new_node->ttm); //create new parent with new_node val
        struct TreeInfo *prev_inOrder = n->prev;


        //fit new_par into tree
        if(n == n->tp->trc) {n->tp->trc = new_par;}
        else {n->tp->tlc = new_par;}

        //set children of new par
        new_par->tlc = new_node;
        new_par->trc = n;

        //set parent of new par
        new_par->tp = n->tp;

        //set parent of new children
        new_node->tp = new_par;
        n->tp = new_par;

        //update leaf list
        new_node->next = n;
        new_node->prev = prev_inOrder;
        n->prev = new_node;
        if(prev_inOrder) {
            prev_inOrder->next = new_node;
        }
    } else {
        struct TreeInfo *new_par = LO_BST_newNode(n->tId,n->ttm); //create new parent with n val

        //fit new_par into tree
        if(n == n->tp->trc) {n->tp->trc = new_par;}
        else {n->tp->tlc = new_par;}

        //set children of new par
        new_par->tlc = n;
        new_par->trc = new_node;

        //set parent of new_par
        new_par->tp = n->tp;

        //set parent of new children
        n->tp = new_par;
        new_node->tp = new_par;

        //update leaf nodes' list
        new_node->next = n->next;
        if(n->next) {
            n->next->prev = new_node;
        }
        n->next = new_node;
        new_node->prev = n;

    }

    return 0;
}

int LO_BST_Delete(struct TreeInfo **root, int _ttm) {

    struct TreeInfo *n = LO_BST_Lookup(*root,_ttm);

    if(!n) {return -1;} //if tree is empty or node was not found

    if(*root == n) { //if root has only one leaf, the one to be deleted
        *root = NULL; //set to null
        return 0;
    }

    struct TreeInfo *par = n->tp; //parent of n node that will also be deleted
    struct TreeInfo *new_par_left_leaf;

    if(n == par->tlc) { //if n is left child of its parent
                        //parent will be replaced by its right child
                        //right child's left most leaf must also be updated

        new_par_left_leaf = LO_BST_Min(par->trc);

        //update leaf list
        new_par_left_leaf->prev = n->prev;
        if(n->prev) {n->prev->next = new_par_left_leaf;}

        //update new_par's position in tree
        if(par->tp) {  //if par isn't root

            //place new_par in the place of old par
            if(par->tp->tlc == par) {par->tp->tlc = par->trc;}
            else {par->tp->trc = par->trc;}

        } else { //if parent node is root of tree
            *root = par->trc;
        }

        //update new_par's parent
        par->trc->tp = par->tp;

    } else { //if n is right child of its parent
             //parent will be replaced by its left child
             //left child's left most leaf must also be updated


        new_par_left_leaf = LO_BST_Min(par->tlc);

        //update leaf list
        new_par_left_leaf->next = n->next;
        if(n->next) {n->next->prev = new_par_left_leaf;}

        //update new_par's position in tree
        if(par->tp) { //if par isn't root of tree

            //place new_par in the place of old par
            if(par->tp->tlc == par) {par->tp->tlc = par->tlc;}
            else {par->tp->trc = par->tlc;}

        } else { //if parent is root node
            *root = par->tlc;
        }

        //update new_par's parent
        par->tlc->tp = par->tp;

    }

    return 1;


}


struct TreeInfo *LO_BST_Lookup(struct TreeInfo *root, int _ttm) {

    if(!root) {return NULL;} //if tree is empty

    while(!LO_BST_isLeaf(root)) { //traverse tree until you hit a leaf
        if(root->ttm < _ttm) {
            root = root->trc;
        } else {
            root = root->tlc;
        }
    }

    return root;
}

struct TreeInfo *LO_BST_Min(struct TreeInfo *root) {

    if(!root) {return NULL;} //if tree is empty

    while(!LO_BST_isLeaf(root)) {
        root = root->tlc;
    }

    return root;
}

struct TreeInfo *LO_BST_getLeftMostAddress(struct TreeInfo **root) {

    if(!(*root)) {return NULL;}

    struct TreeInfo *n = *root;
    while(!LO_BST_isLeaf(n)) {
        n = n->tlc;
    }

    return n;
}


int LO_BST_isLeaf(struct TreeInfo *n) {

    if(!n) {
        return NULL;
    }

    return (!n->tlc && !n->trc);
}

void LO_BST_PrintList(struct TreeInfo *root, int gId) {
    root = LO_BST_Min(root);


    fprintf(stderr,"<");
    while(root) {
        fprintf(stderr,"%d(<%d>)",root->tId,gId);
        if(root->next) {fprintf(stderr,",");}
        root = root->next;
    }

    fprintf(stderr,">,\n");

}


size_t LO_BST_SizeOf() {
    return sizeof(struct TreeInfo);
}