#include <time.h>
#include <stdio.h>
#include "Sub_Hash_Map.h"



unsigned static const int p = 2147483647;
unsigned static int m;

static int a;
static int b;


unsigned int Universal_Hash_Function(unsigned int _sId) {
    return (((a * _sId) + b ) % p) % m; //return ((ax + b) mod p) mod m
}

struct SubInfo **HT_Initialize(unsigned int _p, unsigned int _m) {

    m = _m;

    srand(time(NULL));
    a = (rand() % (p -1)) + 1; //a = [1,p)
    b = (rand() % (p -1)); // b = [0,p)

    printf("%d %d",a,b);

    struct SubInfo **tmp = malloc(m * sizeof (struct SubInfo *));


    for(int i = 0; i < m; i++) {
        tmp[i] = NULL;
    }

    return tmp;

}

struct SubInfo *HT_newNode(int _sId, int _stm, int *gids_arr) {
    struct SubInfo *tmp = malloc(sizeof(struct SubInfo));

    tmp->sId = _sId;
    tmp->stm = _stm;
    tmp->snext = NULL;

    for(int i = 0; i < MG; i++) {
        tmp->sgp[i] = 1;
        tmp->tgp[i] = 1;
    }

    int i = 0;
    while(i < MG && gids_arr[i] != -1 && gids_arr[i] < MG) {
        int val = gids_arr[i];
        tmp->sgp[val] = NULL;
        tmp->tgp[val] = NULL;
        i++;
    }



    return tmp;

}

int HT_Insert(struct SubInfo **hash_map, struct SubInfo *new_node) {

    //if node already exists in hash map
    if(HT_Lookup(hash_map,new_node->sId)) {
        return -1;
    }

    unsigned int index = Universal_Hash_Function(new_node->sId);
    struct SubInfo *n = hash_map[index];

    //if chain is empty
    if(!n) {
        hash_map[index] = new_node;
        return 1;
    }

    //if new_node position should be in root of chain
    if(new_node->sId < n->sId) {
        new_node->snext = n;
        hash_map[index] = new_node;
        return 0;
    }

    //traverse chain until you find correct position
    while(n->snext && n->snext->sId < new_node->sId) {
        n = n->snext;
    }

    struct SubInfo **n_helper = &n; //helper pointer to update hash_map for new_node's insertion

    new_node->snext = (*n_helper)->snext;
    (*n_helper)->snext = new_node;

    return 0;
}

int HT_Delete(struct SubInfo **hash_map, int _sId) {

    //if sub id does not exist
    if(!HT_Lookup(hash_map,_sId)) {
        return 0;
    }

    unsigned int index = Universal_Hash_Function(_sId);
    struct SubInfo *n = hash_map[index];

    //if sub is root of chain
    if(n->sId == _sId) {
        hash_map[index] = n->snext;
        return 1;
    }

    //traverse chain unti snext is desired sub
    while(n->snext && n->snext->sId != _sId) {
        n = n->snext;
    }

    struct SubInfo **n_helper = &n; //helper pointer that updates hash_map to delete sub
    (*n_helper)->snext = n->snext->snext;

    return 1;

}

struct SubInfo *HT_Lookup(struct SubInfo **hash_map, int _sId) {
    unsigned int index = Universal_Hash_Function(_sId);

    struct SubInfo *tmp = hash_map[index];

    while(tmp && tmp->sId != _sId) {
        tmp = tmp->snext;
    }

    return tmp;
}


struct TreeInfo **HT_getTGP(struct SubInfo *hash_map) {
    return hash_map->tgp;
}

struct TreeInfo **HT_getSGP(struct SubInfo *hash_map) {
    return hash_map->sgp;
}

unsigned int HT_getM() {
    return m;
}

int HT_count(struct SubInfo **root) {
    struct SubInfo *tmp;

    int cnt = 0;
    for(int i = 0; i < m; i++) {
        tmp = root[i];
        while(tmp) {
            cnt++;
            tmp = tmp->snext;
        }
    }

    return cnt;
}

void HT_Print(struct SubInfo **root) {
    struct SubInfo *tmp;

    fprintf(stderr,"SUBSCRIBERLIST = <");

    for(int i = 0; i < m; i++) {
        tmp = root[i];
        while(tmp) {
            fprintf(stderr,"%d,",tmp->sId);
            tmp = tmp->snext;
        }
    }
    fprintf(stderr,">\n");
}

void HT_PrintTgp(struct SubInfo *sub) {
    fprintf(stderr,"GROUPLIST =\n");

    for(int i = 0; i < MG; i++) {
        if(sub->tgp[i] != 1) {
            fprintf(stderr,"<%d>,",i);
            fprintf(stderr,"TREELIST = ");
            LO_BST_PrintList(sub->tgp[i],i);
        }
    }
}