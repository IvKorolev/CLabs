#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

enum errors str_to_int(const char *x, long int *res);
int string_length(const char* str);
enum errors reverse_str(const char* str, char** result);
enum errors high_register(const char* str, char** result);
enum errors new_str(const char* str, char** result);
void concat_string(char* str, char** result, int* len);
enum errors concatenate_all(char** strs, int count_str, char** result, unsigned int res);


#endif //CLABS_OPERATIONS_H
