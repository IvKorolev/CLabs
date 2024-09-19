#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

#define ld long double

enum errors{
    INVALID_MEMORY,
    INVALID_INPUT,
    OK,
};

enum errors str_to_long_double(const char *x, ld *res){
    char *last;
    *res = strtold(x, &last);
    if (errno == ERANGE && (*res == LDBL_MIN || *res == LDBL_MAX)){
        return INVALID_INPUT;
    }
    if (errno != 0 && *res == 0){
        return INVALID_INPUT;
    }
    if (*last != '\0'){
        return INVALID_INPUT;
    }
    return OK;
}

double f_a(double x) {
    if (x == 0) return 0;  // Избегаем деления на 0
    return log(1 + x) / x;
}

double f_b(double x) {
    return exp(-x * x / 2);
}

double f_c(double x) {
    return log(1 / (1 - x));
}

double f_d(double x) {
    return pow(x, x);
}

double trapezoidal(double (*f)(double), double a, double b, ld epsilon) {
    double previous_result, current_result = 0;
    int n = 1;
    double h, x;

    do {
        previous_result = current_result;
        current_result = 0;
        h = (b - a) / n;

        for (int i = 1; i < n; i++) {
            x = a + i * h;
            current_result += f(x);
        }

        current_result = (current_result * 2 + f(a) + f(b)) * h / 2;
        n *= 2;
    } while (fabs(current_result - previous_result) > epsilon);

    return current_result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Ошибка: неправильный ввод\n");
        return INVALID_INPUT;
    }
    ld epsilon;
    if(str_to_long_double(argv[1], &epsilon) == INVALID_INPUT) {
        printf("Ошибка ввода\n");
        return INVALID_INPUT;
    };
    double a = 0.0, b = 1.0;

    double result_a = trapezoidal(f_a, a, b, epsilon);
    double result_b = trapezoidal(f_b, a, b, epsilon);
    double result_c = trapezoidal(f_c, a, b, epsilon);
    double result_d = trapezoidal(f_d, a, b, epsilon);

    printf("Интеграл A: %lf\n", result_a);
    printf("Интеграл B: %lf\n", result_b);
    printf("Интеграл C: %lf\n", result_c);
    printf("Интеграл D: %lf\n", result_d);

    return 0;
}