/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Header file for the Public Subscribe System,
 * with the structures and function prototypes
 *
 ***************************************************************
 */

#ifndef pss_h
#define pss_h
#define MG 64
#include "Insert_info.h"
#include "Subscription.h"
#include "subscriber_info.h"


/* MG ALSO EXISTS IN subscriber_info.h, Insert_Info.h */
struct Group {
    int gId;
    struct Subscription *ggsub;
    struct Info *gfirst;
    struct Info *glast;
};

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(struct Group *g);

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void);

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr, struct Group *g, struct SubInfo **s);

/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr, struct Group *g, struct SubInfo **s);

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(SubInfo  *s, int sId);

/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(struct Group  *g, struct SubInfo **s,int sId);

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(struct Group *g, struct SubInfo *s, int n);

void Print_Group_Info(struct Group *g, int n, int* gids_arr, int gids_arr_sz);

void Print_Group_Sub(struct Group *g, struct SubInfo *s, int n, int* gids_arr,int size_of_gids_arr);

#endif /* pss_h */



