cmake_minimum_required(VERSION 3.21)
project(3_Phase_power_computation C)

set(CMAKE_C_STANDARD 99)

add_executable(3_Phase_power_computation main.c File_open.h File_open.c computation.h computation.c)
