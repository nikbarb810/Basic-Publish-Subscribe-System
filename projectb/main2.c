#include <stdio.h>
#include <assert.h>
#include "InfoTree.h"
#include "LO_TreeInfo.h"
#include "Sub_Hash_Map.h"


int main() {

//    struct TreeInfo *root = LO_BST_Initialize();
//
//
//    struct TreeInfo *n1 = LO_BST_newNode(1,20);
//    struct TreeInfo *n2 = LO_BST_newNode(2,10);
//    struct TreeInfo *n3 = LO_BST_newNode(3,15);
//    struct TreeInfo *n4 = LO_BST_newNode(4,5);
//    struct TreeInfo *n5 = LO_BST_newNode(5,3);
//    struct TreeInfo *n6 = LO_BST_newNode(0,30);
//    struct TreeInfo *n7 = LO_BST_newNode(0,300);
//
//
//    LO_BST_Insert(&root,n1);
//    LO_BST_Insert(&root,n2);
//    LO_BST_Insert(&root,n3);
//    LO_BST_Insert(&root,n4);
//    LO_BST_Insert(&root,n5);
//    LO_BST_Insert(&root,n6);
//    LO_BST_Insert(&root,n7);
//
//    LO_BST_Delete(&root,15);
//    printf("test");


    struct SubInfo **hash_table = HT_Initialize(100,1);

    struct SubInfo *n1 = HT_newNode(1,100);
    struct SubInfo *n2 = HT_newNode(7,150);
    struct SubInfo *n3 = HT_newNode(100,120);
    struct SubInfo *n4 = HT_newNode(22,70);


    HT_Insert(hash_table,n4);
    HT_Insert(hash_table,n1);
    HT_Insert(hash_table,n2);
    HT_Insert(hash_table,n3);


    printf(" %d ", HT_Lookup(hash_table,100) == NULL);

    HT_Delete(hash_table,22);

    printf("%d", HT_Lookup(hash_table,100) == NULL);

//    int tmp_igp[64];
//
//    for(int i = 0; i < 64; i++) {
//        tmp_igp[i] = 0;
//    }
//
//
//
//
//
//
//
//    struct Info *root = BST_Initialize();
//
//    struct Info *n1 = BST_newNode(50,15,tmp_igp);
//    struct Info *n2 = BST_newNode(70,200,tmp_igp);
//    struct Info *n3 = BST_newNode(60,50,tmp_igp);
//    struct Info *n4 = BST_newNode(80,500,tmp_igp);
//    struct Info *n5 = BST_newNode(5,70,tmp_igp);
//    struct Info *n7 = BST_newNode(7,20,tmp_igp);
//    struct Info *n10 = BST_newNode(10,10,tmp_igp);
//    struct Info *n6 = BST_newNode(6,69,tmp_igp);
//
//
//    BST_Insert(&root,n1);
//    BST_Insert(&root,n2);
//    BST_Insert(&root,n3);
//    BST_Insert(&root,n4);
////    BST_Insert(&root,n7);
////    BST_Insert(&root,n4);
////    BST_Insert(&root,n10);
////    BST_Insert(&root,n6);
//
//    //printf("%d", BST_Lookup(root,4)->itm);
//
//    BST_Delete(&root,50);
//
//    printf("%d", BST_Lookup(root,70)->iId);
//
//
//


   /* struct Subscription *tmp = L_Create_Node(1);
    struct Subscription *tmp2 = L_Create_Node(2);
    struct Subscription *tmp3 = L_Create_Node(3);

    struct Subscription *root = L_Initialize();

    L_Insert(&root,tmp);
    L_Insert(&root,tmp2);
    L_Insert(&root,tmp3);

    L_PrintList(root);

    L_Delete(&root,2);

    L_PrintList(root); */
/*    struct SubInfo *tmp = SL_CreateNode(0,80,NULL);
//    struct SubInfo *tmp1 = SL_CreateNode(1,100,NULL);
//    struct SubInfo *tmp2 = SL_CreateNode(2,50,NULL);
//    struct SubInfo *tmp3 = SL_CreateNode(3,80,NULL);
//    struct SubInfo *tmp4 = SL_CreateNode(4,120,NULL);
//
//    struct SubInfo *root = SL_Initialize();
//
//
//    SL_Insert(&root,tmp);
//    SL_Insert(&root,tmp1);
//    SL_Insert(&root,tmp2);
//    SL_Insert(&root,tmp3);
//    SL_Insert(&root,tmp4);
//
//    SL_Print(root);
//
//    printf("\nTimestamp of sub with id %d: %d\n\n",3, SL_Lookup(root,3)->stm);
//
//    SL_Delete(&root,0);
//
//    SL_Print(root); */
//
//    struct Info *root = DL_Initialize();
//
//    int igp[1024];
//
//    igp[10] = 1;
//    igp[5] = 1;
//    igp[3] = 1;
//
//
//    struct Info *tmp = DL_CreateNode(0,50,igp);
//    struct Info *tmp1 = DL_CreateNode(1,30,igp);
//    struct Info *tmp2 = DL_CreateNode(2,100,igp);
//    struct Info *tmp3 = DL_CreateNode(3,80,igp);
//
//    DL_Insert(&root,tmp);
//    DL_Insert(&root,tmp1);
//    DL_Insert(&root,tmp2);
//    DL_Insert(&root,tmp3);
//
//    DL_Delete(&root,0);
//
//    DL_Print(root);
//
//    printf("test");

}