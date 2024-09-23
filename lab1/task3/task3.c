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

enum errors str_to_long_double(const char *x, ld *res) {
    char symbol;
    if (sscanf(x, "%Lf%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }

    if (*res >= LDBL_MAX || *res <= LDBL_MIN) {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors str_to_int(const char *x, long int *res) {
    char symbol;
    if (sscanf(x, "%ld%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }

    if (*res >= INT_MAX || *res <= INT_MIN) {
        return INVALID_INPUT;
    }

    return OK;
}

int check_overflow_double(const ld* num1, const ld* num2, ld epsilon)
{
    epsilon *= 1;
    long double result = *num1 * *num2;
    return (result - DBL_MAX <= epsilon && result + DBL_MAX >= epsilon);
}

int compare_with_epsilon(ld a, ld b, ld epsilon) {
    return fabsl(a - b) < epsilon;
}

enum errors first(ld a, ld b, ld c, const ld epsilon){
    ld discriminant = b * b - 4 * a * c;

    if (compare_with_epsilon(a, 0.0L, epsilon)) {
        printf("Это не квадратное уравнение\n");
        return INVALID_INPUT;
    }

    if (discriminant < -epsilon) {
        printf("Для коэффициентов %Lf, %Lf, %Lf Корней нет (дискриминант меньше нуля)\n", a, b, c);
    } else if (compare_with_epsilon(discriminant, 0.0L, epsilon)) {
        ld x = -b / (2 * a);
        printf("Для коэффициентов %Lf, %Lf, %Lf Один корень: x = %Lf\n", a, b, c, x);
    } else {
        ld sqrt_discriminant = sqrtl(discriminant);
        ld x1 = (-b + sqrt_discriminant) / (2 * a);
        ld x2 = (-b - sqrt_discriminant) / (2 * a);
        printf("Для коэффициентов %Lf, %Lf, %Lf Два корня: x1 = %Lf, x2 = %Lf\n", a, b, c, x1, x2);
    }
    return OK;
}

void permutations(ld a, ld b, ld c, const ld epsilon) {
    first(a, b, c, epsilon);
    if (!compare_with_epsilon(b, c, epsilon)) {
        first(a, c, b, epsilon);
    }
    if (!compare_with_epsilon(a, b, epsilon)) {
        first(b, a, c, epsilon);
    }
    if (!compare_with_epsilon(a, c, epsilon) && !compare_with_epsilon(b, c, epsilon)) {
        first(b, c, a, epsilon);
    }
    if (!compare_with_epsilon(a, c, epsilon)) {
        first(c, a, b, epsilon);
    }
    if (!compare_with_epsilon(a, b, epsilon) && !compare_with_epsilon(a, c, epsilon)) {
        first(c, b, a, epsilon);
    }
}

enum errors triangle(ld a, ld b, ld c, ld epsilon) {
    if (a < 0 || b < 0 || c < 0) {
        return INVALID_INPUT;
    }

    if(!check_overflow_double(&a, &a, epsilon) ||
        !check_overflow_double(&b, &b, epsilon) ||
        !check_overflow_double(&c, &c, epsilon))
        return ERROR_OVERFLOW;

    ld max_side = fmaxl(fmaxl(a, b), c);
    ld other1, other2;

    if (compare_with_epsilon(max_side, a, epsilon)) {
        other1 = b;
        other2 = c;
    } else if (compare_with_epsilon(max_side, b, epsilon)) {
        other1 = a;
        other2 = c;
    } else {
        other1 = a;
        other2 = b;
    }

    if (compare_with_epsilon(max_side * max_side, other1 * other1 + other2 * other2, epsilon)) {
        printf("Числа %Lf, %Lf и %Lf могут быть сторонами прямоугольного треугольника\n", a, b, c);
    } else {
        printf("Числа %Lf, %Lf и %Lf не могут быть сторонами прямоугольного треугольника\n", a, b, c);
    }
    return OK;
}

int main(int argc, char* argv[]){
    switch(argv[1][1]){
        case 'q':
            if (argc != 6) {
                printf("Ошибка: недостаточно аргументов.\n");
                return INVALID_INPUT;
            }
            ld epsilon, a, b, c;
            if (str_to_long_double(argv[2], &epsilon) != OK ||
                str_to_long_double(argv[3], &a) != OK ||
                str_to_long_double(argv[4], &b) != OK ||
                str_to_long_double(argv[5], &c) != OK)
            {
                printf("Ошибка: одно из чисел невалидно\n");
                return INVALID_INPUT;
            }
            permutations(a, b, c, epsilon);
            break;

        case 'm':
            if (argc != 4) {
                printf("Ошибка: недостаточно аргументов.\n");
                return INVALID_INPUT;
            }
            long int number1, number2, base = 10;

            if (str_to_int(argv[2], &number1) != OK ||
                str_to_int(argv[3], &number2) != OK || number1 == 0 || number2 == 0)
            {
                printf("Ошибка: одно из чисел невалидно или равно 0\n");
                return INVALID_INPUT;
            }
            if(number1 % number2 == 0)
            {
                printf("Число %ld делится на %ld без остатка\n", number1, number2);
            }
            else
            {
                printf("Число %ld не делится на %ld без остатка\n", number1, number2);
            }
            break;

        case 't':
            if (argc != 6) {
                printf("Ошибка: недостаточно аргументов.\n");
                return INVALID_INPUT;
            }
            ld eps, first, second, third;
            if (str_to_long_double(argv[2], &eps) != OK ||
                str_to_long_double(argv[3], &first) != OK ||
                str_to_long_double(argv[4], &second) != OK ||
                str_to_long_double(argv[5], &third) != OK)
            {
                printf("Ошибка: одно из чисел невалидно\n");
                return INVALID_INPUT;
            }
            enum errors result = triangle(first, second, third, eps);
            if (result == INVALID_INPUT){
                printf("Ошибка ввода сторон\n");
                return INVALID_INPUT;
            } else if (result == ERROR_OVERFLOW){
                printf("Ошибка: переполнение памяти\n");
            }

            break;

        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            break;
    }
    return 0;
}
