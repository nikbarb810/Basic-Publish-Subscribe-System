#include <malloc.h>
#include <assert.h>

#ifndef LO_TREE_INFO_H
#define LO_TREE_INFO_H
struct TreeInfo {
    int tId;
    int ttm;
    struct TreeInfo *tlc;
    struct TreeInfo *trc;
    struct TreeInfo *tp;
    struct TreeInfo *next;
    struct TreeInfo *prev;
};


struct TreeInfo *LO_BST_Initialize();

struct TreeInfo *LO_BST_newNode(int _tId, int _ttm);

int LO_BST_Insert(struct TreeInfo **root, struct TreeInfo *new_node);

int LO_BST_Delete(struct TreeInfo **root, int _ttm);

struct TreeInfo *LO_BST_Lookup(struct TreeInfo *root, int _ttm);

struct TreeInfo *LO_BST_Min(struct TreeInfo *root);

struct TreeInfo *LO_BST_getLeftMostAddress(struct TreeInfo **root);

void LO_BST_PrintList(struct TreeInfo *root, int gId);

size_t LO_BST_SizeOf();
#endif

