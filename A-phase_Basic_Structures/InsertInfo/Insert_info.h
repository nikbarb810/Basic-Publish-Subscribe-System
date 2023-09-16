#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MG 64

struct Info {
    int iID;
    int itm;
    int igp[64];
    struct Info *inext;
    struct Info *iprev;
};
/**
 * Function allocates memory for a new list.
 *
 * @return a pointer to empty list
 */
struct Info *DL_Initialize();

/**
 * Function allocates memory for a new node and creates it with input parameters.<p>
 * node->inext,iprev is set to NULL by default.<p>
 * iId == -1 is reserved for internal functions, user must input a different value
 * @param _iID Input iId (Must be different than -1)
 * @param _itm Input Timestamp
 * @param _igp Input info group pointer arr
 * @return a pointer to struct Info with input parameters
 */
struct Info *DL_CreateNode(int _iID, int _itm, int *_igp);

/**
 *
 * @param root list that node will be inserted
 * @param new_node node to be added
 * @return 0 on failure; 1/2 on success (2 if root was empty before DL_Insert)
 */
int DL_Insert(struct Info **root, struct Info *new_node);

/**
 *Function traverses list and deletes node with _Sid
 *
 * @param root list that will be traversed
 * @param _Sid subscriber id that will be deleted
 * @return 1 if deletion was successful; 0 if root is empty or node does not exist
 */
int DL_Delete(struct Info **root, int _iID);

/**
 * Function searches list for node with SId = _Sid<p>
 * Function returns a NEW node with the same parameters
 * @param root List that will be searched
 * @param _Sid Desired Lookup node
 * @return A new Info *node with SId = _Sid ; NULL if node does not exist
 */
struct Info *DL_Lookup(struct Info *root, int _iID);

/**
 * Function traverses list and returns a pointer to the last element
 * @param root List that will be searched
 * @return a pointer of Info of the last node
 */
struct Info *DL_Lookup_Last(struct Info *root);

void DL_Print(struct Info *root);

/**
 * Function prints every info's id and returns a pointer to the last node
 * @param s list that will be printed
 * @return a pointer to the last node of Info list
 */
struct Info *DL_Traverse_Print(struct Info *s);