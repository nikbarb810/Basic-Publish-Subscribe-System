#include "subscriber_info.h"



struct SubInfo {
    int Sid;
    int stm;
    struct Info *sgp[MG];
    struct SubInfo *snext;
};

SubInfo *SL_Initialize() {
    struct SubInfo *root = malloc(sizeof(struct SubInfo));
    assert(root);

    root->Sid = -1;
    root->snext = NULL;
    return root;

}


SubInfo *SL_CreateNode(int _Sid, int _stm, struct Info **_sgp) {
    int i;

    if(_Sid == -1) {
        return NULL;
    }
    struct SubInfo *node = malloc(sizeof(struct SubInfo));
    assert(node);

    node->Sid = _Sid;
    node->stm = _stm;
    for(i = 0; i < MG; i++) {
        node->sgp[i] = _sgp[i];
    }
    node->snext = NULL;
    return node;

}

int SL_Insert(SubInfo **root, SubInfo *new_node) {

    struct SubInfo *n = malloc(sizeof(struct SubInfo));
    assert(n);

    /* search if sub's id already exists */
    if(SL_Lookup_ByValue(*root,new_node->Sid)) {
        return EXIT_FAILURE;
    }

    /* if node with new_node->Sid exists in list  */
    if(SL_Lookup_ByValue(*root,new_node->Sid)) {
        return 0; /* return failure */
    }

    /*new_node is the first elem of list*/
    if((*root)->Sid == -1) {
        (*root) = new_node;
        return 1;
    }

    n = *root;

    /*new_node has smaller stm than first elem of root*/
    if(n->stm > new_node->stm) {
        new_node->snext = *root;
        *root = new_node;
        return 1;
    }


    /*traverse list until snext node is where new one will be inserted*/
    while(n->snext && n->snext->stm < new_node->stm) {
        n = n->snext;
    }

    /*insert new_node as snext one from index n*/
    new_node->snext = n->snext;
    n->snext = new_node;

    return 1;
}


int SL_Delete(SubInfo **root, int _Sid) {
    SubInfo *n = malloc(sizeof(SubInfo));
    SubInfo *n1 = malloc(sizeof(SubInfo));
    assert(n);
    assert(n1);

    /*if list is empty*/
    if(!(*root) || (*root)->Sid == -1) {
        return 0;
    }

    n = (*root);
    /*if we want to delete first element*/
    if((*root)->Sid == _Sid) {
        (*root) = n->snext;
        free(n);
        return 1;
    }

    while(n->snext) {
        if(n->snext->Sid == _Sid) {
            n1 = n->snext;
            n->snext = n->snext->snext;
            free(n1);
            return 0;
        }
        n = n->snext;
    }

    return 1;
}

SubInfo *SL_Lookup_ByValue(SubInfo *root, int _Sid) {
    SubInfo *n = root;
    while(n && n->Sid != -1) {
        if(n->Sid == _Sid) {
            SubInfo *tmp = SL_CreateNode(n->Sid,n->stm,n->sgp); //!!!!!!!!!!!!!!!!!!!!
            return tmp;
        }
        n = n->snext;
    }

    return NULL;
}

SubInfo *SL_Lookup_ByReference(SubInfo *root, int _Sid) {
    SubInfo *n = root;
    while(n && n->Sid != -1) {
        if(n->Sid == _Sid) {
            return n;
        }
        n = n->snext;
    }

    return NULL;
}


void SL_Print(SubInfo *root) {
    SubInfo *n = malloc(sizeof(struct SubInfo));
    assert(n);

    n = root;
    fprintf(stderr,"SUBSCRIBERLIST = <");
    while(n) {
        if(n->Sid == -1) {
            break;
        }
        fprintf(stderr,"%d",n->Sid);
        if(n->snext) {
            fprintf(stderr,",");
        }
        n = n->snext;
    }
    fprintf(stderr,">\n");
}

void SL_Print_Sgp(SubInfo *root, int n) {
    int i;

    fprintf(stderr,"<");
    for(i = 0; i < n; i++) {
        if(root->sgp[i] != 1) {
            fprintf(stderr,"%d,",i);
        }
    }
    fprintf(stderr,">");
}

void SL_Print_Indiv(SubInfo *root, int n) {

    while(root) {
        if(root->Sid == -1) {
            break;
        }
        fprintf(stderr,"SUBSCRIBERID = <%d>,",root->Sid);
        fprintf(stderr,"GROUPLIST = ");
        SL_Print_Sgp(root,n);
        fprintf(stderr,"\n");

        root = root->snext;
    }
}

int SL_len(SubInfo *root) {
    int i = 0;
    while(root) {
        i++;
        root = root->snext;
    }

    return i;
}

struct Info **SL_getSgp(SubInfo *root, int _sId) {

    struct SubInfo *n = SL_Lookup_ByReference(root,_sId);

    if(n) {
        return n->sgp;
    }

    return NULL;
}