#include "InfoTree.h"

struct Info *BST_Min(struct Info *root);
void BST_CopyVal(struct Info **dest, struct Info *src);

struct Info *BST_Initialize() {
    return NULL;
}

struct Info *BST_newNode(int _iId, int _itm) {
    struct Info *tmp = malloc(sizeof(struct Info));

    tmp->iId = _iId;
    tmp->itm = _itm;

    tmp->ilc = NULL;
    tmp->irc = NULL;
    tmp->ip = NULL;

    return tmp;
}

int BST_Insert(struct Info **root, struct Info *new_node) {

    struct Info *n;

    // if tree is empty
    if(!(*root)) {
        (*root) = new_node;
        return 0;
    }

    n = *root;

    while(n->irc || n->ilc) {
        if(n->iId < new_node->iId) {
            if(!n->irc) {break;}
            n = n->irc;
        } else {
            if(!n->ilc) {break;}
            n = n->ilc;
        }
    }

    if(n->iId < new_node->iId) {
        n->irc = new_node;
        new_node->ip = n;
    } else {
        n->ilc = new_node;
        new_node->ip = n;
    }

    return 0;

}


int BST_Delete(struct Info **root, int iId) {
    struct Info *n;
    struct Info *min_rt;

    if(!(*root)) {return 1;} //tree is empty

    n = BST_Lookup(*root,iId);

    if(!n) {return 1;} //iId does not exist

    if(!n->irc && !n->ilc) { //if node is leaf

        if(n == n->ip->irc) {n->ip->irc = NULL;} //if node is rc of parent
        else {n->ip->ilc = NULL;} //if node is lc of parent

    } else if(!n->irc &&  n->ilc) {  //if node has left child but no right child
        //replace n with n->ilc

        n->ilc->ip = n->ip; // update child's parent
        if(n == n->ip->irc) {n->ip->irc = n->ilc;} //if node is rc of parent
        else {n->ip->ilc = n->ilc;} //if node is lc of parent

    } else if(n->irc && !n->ilc) { //if node has right child but no left child
        //replace n with n->irc

        n->irc->ip = n->ip;
        if(n == n->ip->irc) {n->ip->irc = n->irc;} //if node is rc of parent
        else {n->ip->ilc = n->irc;} //if node is lc of parent

    } else { // node has 2 children

        min_rt = BST_Min(n->irc); // left-most node in right sub-tree
        BST_CopyVal(&n,min_rt); // copy min_rt values to n
        BST_Delete(&min_rt,min_rt->iId); // delete original min_rt node
    }

    return 0;

}

struct Info *BST_Lookup(struct Info *root, int _iId) {

    if(!root) {return NULL;}

    while(root) {
        if(root->iId < _iId) {
            root = root->irc;
        } else if(root->iId > _iId) {
            root = root->ilc;
        } else {
            return root;
        }
    }

    return NULL;
}

/**
 *  Helper function that finds node with min iId in tree
 * @param root Tree that will be searched
 * @return left-most node in tree; NULL if tree is empty
 */
struct Info *BST_Min(struct Info *root) {

    if(!root) {return NULL;}

    while(root->ilc) { /* find left-most node in tree */
        root = root->ilc;
    }
    return root;  /* return it */
}

void BST_CopyVal(struct Info **dest, struct Info *src) {
    (*dest)->iId = src->iId;
    (*dest)->itm = src->itm;

    for(int i = 0; i < MG; i++) {
        (*dest)->igp[i] = src->igp[i];
    }

    return;
}

