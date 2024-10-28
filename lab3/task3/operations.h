#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

typedef struct Employee{
    int id;
    char name[50];
    char last_name[50];
    double payment;
}Employee;

const char* get_filename(const char* path);
enum errors create_list(FILE* input, Employee** result, int *size);


#endif //CLABS_OPERATIONS_H
