cmake_minimum_required(VERSION 3.22)
project(CLabs C)

set(CMAKE_C_STANDARD 11)

add_executable(CLabs
        lab1/task1/task1.c
        lab1/task3/task3.c
        lab1/task6/task6.c
        lab1/task5/task5.c
        lab1/task4/task4.c
        lab1/task2/task2.c
        lab1/task8/task8.c
        lab1/task10/task10.c
        lab1/task7/task7.c
        lab1/task9/task9.c
        lab2/task1/task1.c
        lab2/task1/functions.c
        lab2/task1/operations.h)

add_executable(Task7 lab1/task7/task7.c)

add_executable(Task3 lab1/task3/task3.c)