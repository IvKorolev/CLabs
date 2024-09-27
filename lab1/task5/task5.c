#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define ld long double

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

enum errors str_to_long_double(const char *x, ld *res){
    char symbol;
    if (sscanf(x, "%Lf%c", res, &symbol) != 1){
        return INVALID_INPUT;
    }

    if (fabsl(*res) >= LDBL_MAX || fabsl(*res) <= LDBL_MIN){
        return INVALID_INPUT;
    }

    return OK;
}

ld factorial(int n){
    ld fact = 1;
    for (int i = 1; i <= n; i++){
        fact *= i;
    }
    return fact;
}

ld sum_a(ld x, ld epsilon){
    ld sum = 0;
    ld term;
    int n = 0;

    do{
        term = powl(x, n) / factorial(n);
        sum += term;
        n++;
    }while (fabsl(term) > epsilon);

    return sum;
}

ld sum_b(ld x, ld epsilon){
    ld sum = 0;
    ld term;
    int n = 0;

    do{
        term = powl(-1, n) * powl(x, 2 * n) / factorial(2 * n);
        sum += term;
        n++;
    }while (fabsl(term) > epsilon);

    return sum;
}

ld sum_c(ld x, ld epsilon){
    ld sum = 0;
    ld term;
    int n = 0;

    do{
        term = powl(3, n) * factorial(n) * powl(x, 2 * n) / factorial(3 * n);
        sum += term;
        n++;
    }while (fabsl(term) > epsilon);

    return sum;
}


ld double_factorial(int n){
    if (n == 0 || n == 1){
        return 1;
    }
    ld fact = 1;
    for (int i = n; i > 1; i -= 2){
        fact *= i;
    }
    return fact;
}

enum errors sum_d(ld x, ld epsilon, ld *res){
    ld sum = 0;
    ld term;
    int n = 1;

    do{
        ld fact_2n_1 = double_factorial(2 * n - 1);
        ld double_fact_2n = double_factorial(2 * n);

        if (double_fact_2n == 0){
            printf("Ошибка: слишком маленький знаменатель при n=%d\n", n);
            return INVALID_INPUT;
        }

        term = powl(-1, n) * fact_2n_1 * powl(x, 2 * n) / double_fact_2n;

        if (isnan(term)){
            return INVALID_MEMORY;
        }

        sum += term;
        n++;
    }while (fabsl(term) > epsilon);
    *res = sum;
    return OK;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Ошибка: неправильный ввод\n");
        return INVALID_INPUT;
    }
    ld x, epsilon;
    if(str_to_long_double(argv[1], &x) != OK){
        printf("Ошибка первого аргумента (х)\n");
        return INVALID_INPUT;
    }

    if(str_to_long_double(argv[2], &epsilon) != OK){
        printf("Ошибка второго аргумента (епсилон)\n");
        return INVALID_INPUT;
    }

    if(epsilon < 0){
        printf("Ошибка ввода второго аргумента (епсилон)\n");
        return INVALID_INPUT;
    }

    ld result_a = sum_a(x, epsilon);
    ld result_b = sum_b(x, epsilon);
    ld result_c = sum_c(x, epsilon);
    ld res = 0;
    enum errors result_d = sum_d(x, epsilon, &res);

    printf("Сумма ряда a: %.15Lf\n", result_a);
    printf("Сумма ряда b: %.15Lf\n", result_b);
    printf("Сумма ряда c: %.15Lf\n", result_c);
    if (result_d == INVALID_MEMORY) {
        printf("Ошибка при вычислении ряда d: получено значение inf\n");
    }
    else if (result_d != INVALID_INPUT){
        printf("Сумма ряда d: %.15Lf\n", res);
    }
    return 0;
}
