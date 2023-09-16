#include <stdio.h>
#include "Subscription.h"

struct Subscription *L_Initialize() {
    struct Subscription *n = malloc(sizeof(struct Subscription));
    assert(n);

    n->Sid = -1;
    n->next = NULL;

    return n;
}

struct Subscription *L_Create_Node(int _Sid) {
    struct Subscription *n = L_Initialize();
    assert(n);

    n->Sid = _Sid;
    n->next = NULL;

    return n;
}

int L_Insert(struct Subscription **root, struct Subscription *new_node) {

    if((*root)->Sid == -1) {
        (*root) = new_node;
        return 1;
    }

    new_node->next = (*root);
    (*root) = new_node;

    return 1;
}

int L_Delete(struct Subscription **root, int _Sid) {
    struct Subscription *n = L_Initialize();

    if((*root)->Sid == _Sid) {
        (*root) = (*root)->next;
        return 1;
    }

    n = (*root);
    /* traverse list until end or next node has id = _Sid */
    while(n->next) {
        if(n->next->Sid == _Sid) {
            n->next = n->next->next;
            return 1;
        }
        n = n->next;
    }

    return 0;

}


struct Subscription *L_Lookup(struct Subscription *root, int _Sid) {
    struct Subscription *tmp = L_Initialize();

    while(root) {
        if(root->Sid == _Sid) {
            tmp = root;
            tmp->next = NULL;
            return tmp;
        }
        root = root->next;
    }

    return NULL;

}

void L_PrintList(struct Subscription *root) {

    fprintf(stderr,"SUBLIST = <");
    while(root) {
        if(root->Sid == -1) {
            break;
        }
        fprintf(stderr,"%d",root->Sid);
        if(root->next) {
            fprintf(stderr, ",");
        }
        root = root->next;
    }
    fprintf(stderr,">");
}