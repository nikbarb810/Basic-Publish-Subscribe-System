#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct SubInfo SubInfo;
#define MG 64
typedef struct Info Info;

/**
 * Function allocates memory for a new list.
 *
 * @return a pointer to empty list
 */
SubInfo *SL_Initialize();

/**
 * Function allocates memory for a new node and creates it with input parameters.<p>
 * node->snext is set to NULL by default.<p>
 * SId == -1 is reserved for internal functions, user must input a different value
 * @param _Sid Input SId
 * @param _stm Input stm
 * @param _sgp Input sgp
 * @return SubInfo *node with specified parameters; NULL if SId == -1
 */
SubInfo *SL_CreateNode(int _Sid, int _stm, struct Info **_sgp);

/**
 * Function inserts new node in list, in ascending order of stm.<p>
 * Node MUST be initialized and have the desired values.
 * @param root List that will be updated
 * @param new_node Node that will be added
 * @returns 1 if insertion was successful; 0 if node with input id exists already
 */
int SL_Insert(SubInfo **root, SubInfo *new_node);

/**
 *Function traverses list and deletes node with SId == _Sid
 *
 * @param root list that will be traversed
 * @param _Sid subscriber id that will be deleted
 * @return 1 if deletion was successful; 0 if root is empty or node does not exist
 */
int SL_Delete(SubInfo **root, int _Sid);

/**
 * Function searches list for node with SId = _Sid<p>
 * Function returns a NEW node with the same parameters
 * @param root List that will be searched
 * @param _Sid Desired Lookup node
 * @return A new SubInfo *node with SId = _Sid ; NULL if node does not exist
 */
SubInfo *SL_Lookup_ByValue(SubInfo *root, int _Sid);

/**
 * Function searches list for node with SId = _Sid<p>
 * Function returns the ACTUAL address of node (reference)
 * @param root List that will be searched
 * @param _Sid Desired Lookup node
 * @return SubInfo *node pointing to desired node; NULL if node does not exist
 */
SubInfo *SL_Lookup_ByReference(SubInfo *root, int _Sid);

void SL_Print(SubInfo *root);

/**
 * Prints
 * @param root List that will be printed
 * @param n Size of SGP array
 */
void SL_Print_Indiv(SubInfo *root, int n);

/**
 *
 * @param root Input list
 * @return number of nodes in list
 */
int SL_len(SubInfo *root);

/**
 * Returns sgp array of #_Sid subscriber in #root list
 * @param root  Input list
 * @param _sId  Subscriber's id
 * @return An array of Info pointers of desired subscriber
 */
struct Info **SL_getSgp(SubInfo *root, int _sId);