cmake_minimum_required(VERSION 3.21)
project(project C)

set(CMAKE_C_STANDARD 11)

add_executable(project
        pss.c
        InsertInfo/Insert_info.c
        SubscriberInfo/subscriber_info.c
        Subscription/Subscription.c
        mainA.c)
