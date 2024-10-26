#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

enum errors first(FILE* input, FILE* output);

#endif //CLABS_OPERATIONS_H
