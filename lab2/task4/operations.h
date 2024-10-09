#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

int check_overflow(double * number);
enum errors str_to_long_double(const char *x, long double *res);
enum errors first(int n, ...);
enum errors second(double *result, double point, int degree, ...);
char* my_strndup(const char *str, size_t n);
int is_kaprekar(long num);
enum errors third(double ** result, int *size, int base, ...);

#endif //CLABS_OPERATIONS_H
