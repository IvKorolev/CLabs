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
enum errors str_to_int(const char *x, long int *res);
enum errors str_to_double(const char *x, double *res);
enum errors first(double* result,int count, ...);

#endif //CLABS_OPERATIONS_H
