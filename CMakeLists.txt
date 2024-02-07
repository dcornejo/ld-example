cmake_minimum_required(VERSION 3.28)
project(liquid-example C)

set(CMAKE_C_STANDARD 17)


add_executable(liquid-example
        main.c
        utils.c
        utils.h
)
target_link_libraries(liquid-example
        liquid m
)
