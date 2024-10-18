#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

int binomial_coeff(int n, int k);
enum errors polynomial_decomposition(double epsilon, double a, double **g, int degree, ...);

#endif //CLABS_OPERATIONS_H
