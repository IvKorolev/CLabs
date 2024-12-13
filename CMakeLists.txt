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
        lab2/task1/operations.h
        lab2/task2/task2.c
        lab2/task2/functions.c
        lab2/task2/operations.h
        lab2/task4/task4.c
        lab2/task4/functions.c
        lab2/task4/operations.h
        lab2/task7/task7.c
        lab2/task7/functions.c
        lab2/task7/operations.h
        lab2/task9/task9.c
        lab2/task9/functions.c
        lab2/task9/operations.h
        lab2/task3/task3.c
        lab2/task3/functions.c
        lab2/task3/operations.h
        lab2/task3/func.c
        lab2/task8/task8.c
        lab2/task8/functions.c
        lab2/task8/operations.h
        lab2/task10/task10.c
        lab2/task10/functions.c
        lab2/task10/operations.h
        lab3/task1/task1.c
        lab3/task1/functions.c
        lab3/task1/operations.h
        lab3/task10/task10.c
        lab3/task10/functions.c
        lab3/task10/operations.h
        lab3/task3/task3.c
        lab3/task3/functions.c
        lab3/task3/operations.h
        lab3/task4/task4.c
        lab3/task4/functions.c
        lab3/task4/operations.h
        lab3/task5/task5.c
        lab3/task5/functions.c
        lab3/task5/operations.h
        lab3/task4/task41.c
        lab3/task9/task9.c
        lab3/task9/functions.c
        lab3/task9/operations.h
        lab4/task1/task1.c
        lab4/task1/functions.c
        lab4/task1/operations.h
        lab4/task7/task7.c
        lab4/task7/functions.c
        lab4/task7/operations.h
        lab5/task1/task1.cpp
        lab5/task3/task3.cpp
        lab5/task4/task4.cpp
        Prepare_to_fund/test.c
        Prepare_to_fund/decart_tree.c
)

add_executable(Task7 lab1/task7/task7.c)

add_executable(Task3 lab1/task3/task3.c)

add_executable(Task5 lab3/task5/task5.c)

add_executable(Task1 lab4/task1/task1.c
                    lab4/task1/functions.c
                    lab4/task1/operations.h)

add_executable(Task74 lab4/task7/task7.c
                lab4/task7/functions.c
                lab4/task7/operations.h)


project(CLabs CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(Clabs1 lab5/task1/task1.cpp)
add_executable(Clabs2 lab5/task2/task2.cpp)
add_executable(Clabs3 lab5/task3/task3.cpp)
add_executable(Clabs4 lab5/task4/task4.cpp)
add_executable(PrepareFund Prepare_to_fund/decart_tree.c)
