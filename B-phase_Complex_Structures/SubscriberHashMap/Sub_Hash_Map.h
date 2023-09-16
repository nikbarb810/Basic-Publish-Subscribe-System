#define MG 64
#include "../LO_TreeInfo/LO_TreeInfo.h"
#include <math.h>

struct SubInfo {
    int sId;
    int stm;
    struct TreeInfo *tgp[MG];
    struct TreeInfo *sgp[MG];
    struct SubInfo *snext;
};

unsigned int Universal_Hash_Function(unsigned int _sId);

struct SubInfo **HT_Initialize(unsigned int p, unsigned int m);

struct SubInfo *HT_newNode(int _sId, int _stm, int *gids_arr);

int HT_Insert(struct SubInfo **hash_map, struct SubInfo *new_node);

int HT_Delete(struct SubInfo **hash_map, int _sId);

struct SubInfo *HT_Lookup(struct SubInfo **hash_map, int _sId);

struct TreeInfo **HT_getTGP(struct SubInfo *hash_map);

struct TreeInfo **HT_getSGP(struct SubInfo *hash_map);

unsigned int HT_getM();

int HT_count(struct SubInfo **root);

void HT_Print(struct SubInfo **root);

void HT_PrintTgp(struct SubInfo *sub);