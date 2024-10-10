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

void get_prime_factors(int base, int factors[], int *factor_count);
int gcd(int a, int b);
void convert_to_fraction(double fraction, int *numerator, int *denominator);
int has_finite_representation(int denominator, int factors[], int factor_count);
void print_check_infinite_representation(int count, int base, ...);


#endif //CLABS_OPERATIONS_H
