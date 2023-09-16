cmake_minimum_required(VERSION 3.21)
project(project C)

set(CMAKE_C_STANDARD 11)

add_executable(project
        pss.c
        Insert_info.c
        subscriber_info.c
        Subscription.c
        oldmain.c)
