cmake_minimum_required(VERSION 3.21)
project(projectb C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(projectb
        InfoTree.c
        LO_TreeInfo.c
        Sub_Hash_Map.c
        pss.c
        Subscription.c
        main.c)
