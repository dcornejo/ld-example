cmake_minimum_required(VERSION 3.28)
project(mod_test C)

set(CMAKE_C_STANDARD 17)

add_executable(mod_test
        modem_example.c)
target_link_libraries(mod_test liquid)
