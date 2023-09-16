cmake_minimum_required(VERSION 3.21)
project(B-phase_Complex_Structures C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(B-phase_Complex_Structures
        InfoTree/InfoTree.c
        LO_TreeInfo/LO_TreeInfo.c
        SubscriberHashMap/Sub_Hash_Map.c
        pss.c
        Subscription/Subscription.c
        mainB.c)
