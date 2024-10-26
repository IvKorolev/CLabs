#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
};

int sum(int num1, int num2);
int negative(int n);
int subtraction(int a, int b);
enum errors first(long int num, int r, char** res, int * capacity, int * count, char * base, int* flag_negative);
void print_num(int flag, char * res, int count, int base);


#endif //CLABS_OPERATIONS_H
