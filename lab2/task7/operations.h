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

enum errors dihotomy(double *result, double left, double right, double epsilon, double(*func)(double));
double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);
double func5(double x);
double func6(double x);

#endif //CLABS_OPERATIONS_H
