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

double power(double x, int n) {
    if (n == 0) {
        return 1.0;  // Базовый случай: x^0 = 1
    }

    // Обработка отрицательной степени
    if (n < 0) {
        return 1.0 / power(x, -n);
    }

    // Рекурсивное вычисление
    double halfPower = power(x * x, n / 2);  // Возведение в квадрат и деление степени пополам

    if (!(n & 1)) {
        return x * halfPower;  // Если степень нечётная
    } else {
        return halfPower;
    }
}

enum errors second(double* result, double chislo, int base){

}