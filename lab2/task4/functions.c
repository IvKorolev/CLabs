#include "operations.h"

int check_overflow(double * number) {
    if(isnan(*number) || isinf(*number))
    {
        return 1;
    }
    return 0;
}

enum errors str_to_long_double(const char *x, long double *res) {
    char symbol;
    if (sscanf(x, "%Lf%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }
    if (fabsl(*res) >= LDBL_MAX) {
        return INVALID_INPUT;
    }
    return OK;
}

double cross_product(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
}

enum errors first(int num_vertices, ...) {
    if (num_vertices < 3) {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, num_vertices);

    double x_prev, y_prev, x_curr, y_curr, x_next, y_next;
    double first_cross_product = 0;
    int is_first = 1;

    double prev_x = va_arg(args, double);
    double prev_y = va_arg(args, double);
    double curr_x = va_arg(args, double);
    double curr_y = va_arg(args, double);

    int is_convex = 1;

    for (int i = 2; i < num_vertices; i++) {
        double next_x = va_arg(args, double);
        double next_y = va_arg(args, double);

        double cross = cross_product(prev_x, prev_y, curr_x, curr_y, next_x, next_y);

        if (is_first) {
            first_cross_product = cross;
            is_first = 0;
        }
        else{
            if ((first_cross_product > 0 && cross < 0) || (first_cross_product < 0 && cross > 0)) {
                va_end(args);
                return INVALID_INPUT;
            }
        }

        prev_x = curr_x;
        prev_y = curr_y;
        curr_x = next_x;
        curr_y = next_y;
    }

    if (is_convex) {
        double next_x = va_arg(args, double);
        double next_y = va_arg(args, double);
        double cross = cross_product(prev_x, prev_y, curr_x, curr_y, next_x, next_y);
        if ((first_cross_product > 0 && cross < 0) || (first_cross_product < 0 && cross > 0)) {
            va_end(args);
            return INVALID_INPUT;
        }
    }

    va_end(args);
    return OK;
}

enum errors second(double *result, double point, int degree, ...){
    va_list(coefficients);
    va_start(coefficients, degree);
    *result = 0;
    double coeff;
    for(int i = 0; i <= degree; i++){
        coeff = va_arg(coefficients, double);
        *result = *result * point + coeff;
        if (check_overflow(result)){
            va_end(coefficients);
            return ERROR_OVERFLOW;
        }
    }
    va_end(coefficients);
    return OK;
}

char* my_strndup(const char *str, size_t n) {
    char *result = (char*)malloc(n + 1);
    if (result == NULL) {
        return NULL;
    }
    strncpy(result, str, n);
    result[n] = '\0';
    return result;
}

int is_kaprekar(long num) {
    long square = num * num;
    char square_str[50];
    snprintf(square_str, sizeof(square_str), "%ld", square);
    int len = strlen(square_str);

    for (int i = 0; i < len; i++) {
        long left = atol(my_strndup(square_str, i));
        long right = atol(square_str + i);

        if (left + right == num && right > 0) {
            return 1;
        }
    }
    return 0;
}

enum errors third(double ** result, int *size, int base, ...) {
    int capacity = 4;
    *result = (double*)malloc(sizeof(double) * capacity);
    if (*result == NULL) {
        return INVALID_MEMORY;
    }

    va_list args;
    va_start(args, base);

    int count = 0;
    while (1) {
        const char *str = va_arg(args, const char*);
        if (str == NULL) break;

        long double num;
        enum errors status = str_to_long_double(str, &num);
        if (status != OK) {
            continue;
        }

        if (is_kaprekar(num)) {
            if (count >= capacity) {
                capacity *= 2;
                *result = (double*)realloc(*result, sizeof(double) * capacity);
                if (*result == NULL) {
                    va_end(args);
                    return INVALID_MEMORY;
                }
            }
            (*result)[count++] = (double)num;
        }
    }
    *size = count;
    va_end(args);
    return OK;
}