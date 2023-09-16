#include <stdio.h>
#include <assert.h>
#include "Insert_info.h"


int main() {

//    struct Info *root = BST_Initialize();
//
//    struct Info *n1 = BST_newNode(1,100);
//    struct Info *n2 = BST_newNode(2,200);
//    struct Info *n3 = BST_newNode(3,50);
//    struct Info *n4 = BST_newNode(4,500);
//    struct Info *n5 = BST_newNode(5,70);
//    struct Info *n7 = BST_newNode(7,20);
//    struct Info *n10 = BST_newNode(10,10);
//    struct Info *n6 = BST_newNode(6,69);
//
//
//    BST_Insert(&root,n2);
//    BST_Insert(&root,n1);
//    BST_Insert(&root,n5);
//    BST_Insert(&root,n3);
//    BST_Insert(&root,n7);
//    BST_Insert(&root,n4);
//    BST_Insert(&root,n10);
//    BST_Insert(&root,n6);
//
//    printf("%d", BST_Lookup(root,4)->itm);
//
//    BST_Delete(&root,5);
//
//    printf("test");
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

    struct Info *root = DL_Initialize();

    int igp[64];

    for(int i = 0; i < 64; i++) {
        igp[i] = 0;
    }

    igp[0] = 150;


    struct Info *tmp = DL_CreateNode(0,50,igp);
    struct Info *tmp1 = DL_CreateNode(1,30,igp);
    struct Info *tmp2 = DL_CreateNode(2,100,igp);
    struct Info *tmp3 = DL_CreateNode(3,80,igp);

    DL_Insert(&root,tmp);
    DL_Insert(&root,tmp1);
    DL_Insert(&root,tmp2);
    DL_Insert(&root,tmp3);

    DL_Delete(&root,0);

    DL_Print(root);

    printf("test");

}