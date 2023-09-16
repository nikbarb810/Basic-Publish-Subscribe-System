#include <stdlib.h>
#include <assert.h>


struct Subscription {
    int Sid;
    struct Subscription *next;
};


struct Subscription *L_Initialize();

struct Subscription *L_Create_Node(int _Sid);

int L_Insert(struct Subscription **root, struct Subscription *new_node);

int L_Delete(struct Subscription **root, int _Sid);

struct Subscription *L_Lookup(struct Subscription *root, int _Sid);

void L_PrintList(struct Subscription *root);
