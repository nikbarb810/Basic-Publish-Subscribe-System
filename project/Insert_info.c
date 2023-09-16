#include "Insert_info.h"



typedef struct Info Info;


Info *DL_Initialize() {
    Info *root = malloc(sizeof(struct Info));
    assert(root);


    root->iID = -1;
    root->inext = NULL;
    root->iprev = NULL;
    return root;
}

/* _igp[] = {i0,i1,i2,.....,-1} */
Info *DL_CreateNode(int _iID, int _itm, int *_igp) {
    Info *n = malloc(sizeof(struct Info));
    int i = 0;
    assert(n);

    n->iID = _iID;
    n->itm = _itm;
    n->inext = NULL;
    n->iprev = NULL;

    for(i = 0; i < MG; i++) {
        n->igp[i] = 0;
    }

    i = 0;
    while(i < MG && _igp[i] != -1 && _igp[i] < MG) {
        n->igp[_igp[i]] = 1;
        i++;
    }

    return n;
}

int DL_Insert(Info **root, Info *new_node) {
    Info *n = malloc(sizeof(struct Info));
    assert(n);

    /* if node already exists in list */
    if(DL_Lookup(*root,new_node->iID)) {
        return 0; /* return failure */
    }

    /*new_node is the first elem of list*/
    if((*root)->iID == -1) {
        (*root) = new_node;
        return 2;
    }

    n = *root;
    /*new_node has smaller itm than first elem of root*/
    if(n->itm > new_node->itm) {
        new_node->inext = *root;
        (*root)->iprev = new_node;
        *root = new_node;
        return 1;
    }

    /*traverse list until inext node is where new one will be inserted*/
    while(n->inext && n->inext->itm < new_node->itm) {
        n = n->inext;
    }

    new_node->inext = n->inext;
    new_node->iprev = n;

    /* if this isn't the last node */
    if(n->inext) {
        n->inext->iprev = new_node; /* link next node's prev to new_node */
    }

    n->inext = new_node;

    return 1;
}

int DL_Delete(Info **root, int _iID) {
    struct Info *n = malloc(sizeof(struct Info));
    struct Info *n1 = malloc(sizeof(struct Info));
    assert(n);
    assert(n1);

    if(!(*root) || (*root)->iID == -1) {
        return 0;
    }

    n = (*root);

    /*if we want to delete first element*/
    if((*root)->iID == _iID) {
        (*root) = n->inext;
        (*root)->iprev = NULL;
        free(n);
        return 1;
    }

    /* traverse list */
    while(n->inext) {
        if(n->inext->iID == _iID) { /* if we want to delete next node */
            n1 = n->inext;
            n->inext = n->inext->inext;
            n->inext->iprev = n;   /* link new next node's prev  */
            free(n1);
            return 1;
        }
        n = n->inext;
    }

    return 0;
}


Info *DL_Lookup(Info *root, int _iID) {
    Info *n = malloc(sizeof(struct Info));
    assert(n);

    n = root;
    while(n && n->iID != -1) {
        if(n->iID == _iID) {
            Info *tmp = DL_CreateNode(n->iID,n->itm,n->igp);
            return tmp;
        }
        n = n->inext;
    }

    return NULL;
}

/*
 * returns a pointer to last element of input list
 */
struct Info *DL_Lookup_Last(struct Info *root) {

    assert(root);

    while(root->inext) {
        root = root->inext;
    }
    return root;

}

void DL_Print(Info *root) {

    fprintf(stderr,"INFOLIST = <");
    while(root) {
        if(root->iID == -1) {
            break;
        }
        fprintf(stderr,"%d",root->iID);
        if(root->inext) {
            fprintf(stderr,",");
        }
        root = root->inext;
    }
    fprintf(stderr,">");
}

struct Info *DL_Traverse_Print(struct Info *s) {

    fprintf(stderr,"INFOLIST = <");
    if(!s) {
        fprintf(stderr,">");
        return s;
    }


    /* traverse list */
    while(s->inext) {
        fprintf(stderr,"%d",s->iID); /* print current id */
        if(s->inext) {
            fprintf(stderr,","); /* comma formating */
        }
        s = s->inext;
    }
    fprintf(stderr,"%d>",s->iID); /* print last id */

    return s;
}