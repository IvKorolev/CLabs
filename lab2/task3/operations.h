#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define BUFFER_SIZE 1024

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

void computeLPSArray(const char *substring, int M, int *lps);
void KMPSearch(const char *substring, const char *str, int line_number, const char *file_path);
void find_in_files(const char *substring, int file_count, ...);

#endif //CLABS_OPERATIONS_H
