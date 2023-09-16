#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MG 64

struct Info {
    int iId;
    int itm;
    int igp[MG];
    struct Info *ilc;
    struct Info *irc;
    struct Info *ip;
};

struct Info *BST_Initialize();

struct Info *BST_newNode(int _iId, int _itm, int *_igp);

/**
 *
 * @param root Tree that node will be added to
 * @param new_node Node that will be added
 * @return -1 on failure; 0 on success; 1 if tree was empty before insertion
 */
int BST_Insert(struct Info **root, struct Info *new_node);

int BST_Delete(struct Info **root, int iId);

struct Info *BST_Lookup(struct Info *root, int _iId);

void BST_Print(struct Info *root);