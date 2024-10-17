#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

enum errors reverse_str(const char* str, char** result);
enum errors first(char **result, int base, int count, ...);

#endif //CLABS_OPERATIONS_H
