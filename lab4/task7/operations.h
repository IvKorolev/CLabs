#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
    NOT_DECLARED,
    NOT_FOUND,
};

typedef struct MemoryCell{
    char* name;
    int value;
}MemoryCell;

enum errors str_to_int(const char *x, long int *res);
int compare(const void* a, const void* b);
enum errors check_if_print(const char* buffer, MemoryCell** res, int size);
enum errors search_value_to_new(MemoryCell** res, char* argument, int size, long int* resultation);
enum errors add_Cell(MemoryCell*** res, char* first_argument, long int num, int* size, int* capacity);
enum errors process_line(char* buffer, MemoryCell*** res, int* size, int* capacity);
enum errors process_file(FILE* input, MemoryCell*** res);



#endif //CLABS_OPERATIONS_H
