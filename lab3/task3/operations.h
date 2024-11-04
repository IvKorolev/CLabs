#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#define PATH_MAX 4096

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int compare_files(const char* path1, const char* path2);
enum errors valid_name(char* name);
enum errors create_list(FILE* input, Employee** result, int *size);
int compare_ascending(const void* a, const void* b);
int compare_descending(const void* a, const void* b);
int first(const void* a, const void* b);


#endif //CLABS_OPERATIONS_H
