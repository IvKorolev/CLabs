#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define ld long double

enum errors {
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

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

enum errors str_to_long_double(const char *x, ld *res) {
    char symbol;
    if (sscanf(x, "%Lf%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }
    if (fabsl(*res) >= LDBL_MAX) {
        return INVALID_INPUT;
    }
    return OK;
}

int check_overflow_double(const ld *num1, const ld *num2, ld epsilon) {
    epsilon *= 1;
    long double result = *num1 * *num2;
    return (result - DBL_MAX <= epsilon && result + DBL_MAX >= epsilon);
}

int compare_with_epsilon(ld a, ld b, ld epsilon) {
    return fabsl(a - b) < epsilon;
}

void print_root(ld x) {
    if (compare_with_epsilon(x, 0.0L, 1e-9L)) {
        printf("x = 0.000000");
    } else {
        printf("x = %Lf", x);
    }
}

enum errors solve_quadratic(ld a, ld b, ld c, const ld epsilon) {
    if (compare_with_epsilon(a, 0.0L, epsilon)) {
        if (compare_with_epsilon(b, 0.0L, epsilon)) {
            printf("Это не уравнение\n");
            return INVALID_INPUT;
        } else {
            ld x = -c / b;
            printf("Это линейное уравнение: ");
            print_root(x);
            printf("\n");
            return OK;
        }
    }

    ld discriminant = b * b - 4 * a * c;

    if (discriminant < -epsilon) {
        printf("Корней нет (дискриминант меньше нуля)\n");
    }
    else if (compare_with_epsilon(discriminant, 0.0L, epsilon)){
        ld x = -b / (2 * a);
        printf("Один корень: ");
        print_root(x);
        printf("\n");
    }
    else{
        ld sqrt_discriminant = sqrtl(discriminant);
        ld x1 = (-b + sqrt_discriminant) / (2 * a);
        ld x2 = (-b - sqrt_discriminant) / (2 * a);
        printf("Два корня: ");
        print_root(x1);
        printf(", ");
        print_root(x2);
        printf("\n");
    }
    return OK;
}

int is_unique(ld a1, ld b1, ld c1, ld a2, ld b2, ld c2, ld epsilon) {
    return !(compare_with_epsilon(a1, a2, epsilon) &&
             compare_with_epsilon(b1, b2, epsilon) &&
             compare_with_epsilon(c1, c2, epsilon));
}

void check_permutations(ld a, ld b, ld c, ld epsilon) {
    int processed_permutations = 0;

    ld permutations[6][3] = {
            {a, b, c},
            {a, c, b},
            {b, a, c},
            {b, c, a},
            {c, a, b},
            {c, b, a}
    };

    for (int i = 0; i < 6; i++) {
        int is_new_permutation = 1;

        for (int j = 0; j < processed_permutations; j++) {
            if (!is_unique(permutations[i][0], permutations[i][1], permutations[i][2],
                           permutations[j][0], permutations[j][1], permutations[j][2], epsilon)) {
                is_new_permutation = 0;
                break;
            }
        }

        if (is_new_permutation) {
            printf("Перестановка: a = %Lf, b = %Lf, c = %Lf\n", permutations[i][0], permutations[i][1], permutations[i][2]);
            solve_quadratic(permutations[i][0], permutations[i][1], permutations[i][2], epsilon);

            permutations[processed_permutations][0] = permutations[i][0];
            permutations[processed_permutations][1] = permutations[i][1];
            permutations[processed_permutations][2] = permutations[i][2];
            processed_permutations++;
        }
    }
}

enum errors triangle(ld a, ld b, ld c, ld epsilon) {
    if (a < 0 || b < 0 || c < 0) {
        return INVALID_INPUT;
    }
    if (!check_overflow_double(&a, &a, epsilon) ||
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
        printf("Числа %Lf, %Lf и %Lf могут быть сторонами треугольника\n", a, b, c);
    } else {
        printf("Числа %Lf, %Lf и %Lf не могут быть сторонами треугольника\n", a, b, c);
    }
    return OK;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Ошибка ввода\n");
        return INVALID_INPUT;
    }
    if (!((argv[1][0] == '/' || argv[1][0] == '-') && (argv[1][2] == '\0'))) {
        printf("Ошибка ввода флага\n");
        return INVALID_INPUT;
    }
    switch (argv[1][1]) {
        case 'q':
            if (argc < 6) {
                printf("Ошибка: недостаточно аргументов\n");
                return INVALID_INPUT;
            }

            ld epsilon, a, b, c;
            if (str_to_long_double(argv[2], &epsilon) != OK ||
                str_to_long_double(argv[3], &a) != OK ||
                str_to_long_double(argv[4], &b) != OK ||
                str_to_long_double(argv[5], &c) != OK) {
                printf("Ошибка: одно из чисел невалидно\n");
                return INVALID_INPUT;
            }

            if (compare_with_epsilon(a, 0.0L, epsilon) &&
                compare_with_epsilon(b, 0.0L, epsilon) &&
                compare_with_epsilon(c, 0.0L, epsilon)) {
                printf("Ошибка: все три аргумента равны нулю\n");
                return INVALID_INPUT;
            }

            check_permutations(a, b, c, epsilon);
            break;
        case 'm':
            if (argc != 4) {
                printf("Ошибка: недостаточно аргументов\n");
                return INVALID_INPUT;
            }
            long int number1, number2;
            if (str_to_int(argv[2], &number1) != OK ||
                str_to_int(argv[3], &number2) != OK || number1 == 0 || number2 == 0) {
                printf("Ошибка: одно из чисел невалидно\n");
                return INVALID_INPUT;
            }
            if (number1 % number2 == 0) {
                printf("Число %ld делится на %ld без остатка\n", number1, number2);
            } else {
                printf("Число %ld не делится на %ld без остатка\n", number1, number2);
            }
            break;
        case 't':
            if (argc != 6) {
                printf("Ошибка: недостаточно аргументов\n");
                return INVALID_INPUT;
            }
            ld eps, first, second, third;
            if (str_to_long_double(argv[2], &eps) != OK ||
                str_to_long_double(argv[3], &first) != OK ||
                str_to_long_double(argv[4], &second) != OK ||
                str_to_long_double(argv[5], &third) != OK) {
                printf("Ошибка: одно из чисел невалидно\n");
                return INVALID_INPUT;
            }
            enum errors result = triangle(first, second, third, eps);
            if (result == INVALID_INPUT) {
                printf("Ошибка ввода сторон\n");
                return INVALID_INPUT;
            } else if (result == ERROR_OVERFLOW) {
                printf("Ошибка переполнения памяти\n");
            }
            break;
        default:
            printf("Ошибка: такого флага нет %s\n", argv[1]);
            break;
    }
    return 0;
}