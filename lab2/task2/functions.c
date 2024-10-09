#include "operations.h"

int check_overflow(double * number) {
    if(isnan(*number) || isinf(*number))
    {
        return 1;
    }
    return 0;
}

enum errors str_to_int(const char *x, long int *res) {
    char symbol;
    if (sscanf(x, "%ld%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }

    if (abs(*res) >= INT_MAX || abs(*res) <= INT_MIN) {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors str_to_double(const char *x, double *res){
    char symbol;
    if (sscanf(x, "%lf%c", res, &symbol) != 1){
        return INVALID_INPUT;
    }

    if (fabs(*res) >= DBL_MAX || fabs(*res) <= DBL_MIN){
        return INVALID_INPUT;
    }

    return OK;
}

enum errors first(double* result, int count, ...){
    if (count <= 0){
        return INVALID_INPUT;
    }
    va_list start;
    va_start(start, count);
    *result = 1.0;
    for (int i = 0; i < count; i++){
        *result *= va_arg(start, double);
        if (check_overflow(result)){
            va_end(start);
            return ERROR_OVERFLOW;
        }
    }
    *result = pow(*result, 1.0 / count);
    va_end(start);
    return OK;
}

enum errors second(double x, int n, double *result) {
    if (n == 0) {
        *result = 1.0;
        return OK;
    }

    if (n < 0) {
        if (x == 0.0) {
            return INVALID_INPUT;
        }
        enum errors status = second(x, -n, result);
        if (status == OK) {
            *result = 1.0 / *result;
        }
        return status;
    }

    double halfResult;
    enum errors status = second(x * x, n / 2, &halfResult);
    if (status != OK) {
        return status;
    }
    if (halfResult > DBL_MAX || halfResult < -DBL_MAX) {
        return ERROR_OVERFLOW;
    }

    if (n & 1) {
        *result = x * halfResult;
    } else {
        *result = halfResult;
    }

    return OK;
}