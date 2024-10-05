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

int check_overflow_double(const ld *num1, const ld *num2, ld epsilon) {
    epsilon *= 1;
    long double result = *num1 * *num2;
    return (result - DBL_MAX <= epsilon && result + DBL_MAX >= epsilon);
}

int compare_with_epsilon(ld a, ld b, ld epsilon) {
    return fabsl(a - b) < epsilon;
}

enum errors first(ld a, ld b, ld c, const ld epsilon) {
    if (compare_with_epsilon(a, 0.0L, epsilon) && compare_with_epsilon(b, 0.0L, epsilon)) {
        printf("For coefficients %Lf, %Lf, %Lf the equation has no meaning (all coefficients are zero)\n", a, b, c);
        return INVALID_INPUT;
    }

    if (compare_with_epsilon(a, 0.0L, epsilon)) {
        if (!compare_with_epsilon(b, 0.0L, epsilon)) {
            ld x = -c / b;
            printf("For coefficients %Lf, %Lf, %Lf Linear equation, one root: x = %Lf\n", a, b, c, x);
        } else {
            printf("For coefficients %Lf, %Lf, %Lf The equation has no meaning\n", a, b, c);
        }
        return OK;
    }

    ld discriminant = b * b - 4 * a * c;

    if (discriminant < -epsilon) {
        printf("For coefficients %Lf, %Lf, %Lf No roots (discriminant less than zero)\n", a, b, c);
    } else if (compare_with_epsilon(discriminant, 0.0L, epsilon)) {
        ld x = -b / (2 * a);
        printf("For coefficients %Lf, %Lf, %Lf One root: x = %Lf\n", a, b, c, x);
    } else {
        ld sqrt_discriminant = sqrtl(discriminant);
        ld x1 = (-b + sqrt_discriminant) / (2 * a);
        ld x2 = (-b - sqrt_discriminant) / (2 * a);
        printf("For coefficients %Lf, %Lf, %Lf Two roots: x1 = %Lf, x2 = %Lf\n", a, b, c, x1, x2);
    }
    return OK;
}

/*void permutations(ld a, ld b, ld c, const ld epsilon) {
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
    if (!compare_with_epsilon(a, c, epsilon) && !compare_with_epsilon(a, b, epsilon)) {
        first(c, a, b, epsilon);
    }
    if (!compare_with_epsilon(b, c, epsilon) && !compare_with_epsilon(a, b, epsilon)) {
        first(c, b, a, epsilon);
    }
}*/

void generate_permutations(ld a, ld b, ld c, const ld epsilon, ld *arr, int depth) {
    if (depth == 3) {
        first(arr[0], arr[1], arr[2], epsilon);
        return;
    }
    ld temp;
    for (int i = depth; i < 3; i++) {
        // Swap
        temp = arr[depth];
        arr[depth] = arr[i];
        arr[i] = temp;

        // Recur
        generate_permutations(a, b, c, epsilon, arr, depth + 1);

        // Swap back
        temp = arr[depth];
        arr[depth] = arr[i];
        arr[i] = temp;
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
        printf("The numbers %Lf, %Lf, and %Lf can be the sides of a right triangle\n", a, b, c);
    } else {
        printf("The numbers %Lf, %Lf, and %Lf cannot be the sides of a right triangle\n", a, b, c);
    }
    return OK;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Error: incorrect input\n");
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '/' || argv[1][0] == '-') && (argv[1][2] == '\0'))) {
        printf("Input flag error\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1]) {
        case 'q':
            if (argc != 6) {
                printf("Error: not enough arguments.\n");
                return INVALID_INPUT;
            }
            ld epsilon, a, b, c;
            if (str_to_long_double(argv[2], &epsilon) != OK ||
                str_to_long_double(argv[3], &a) != OK ||
                str_to_long_double(argv[4], &b) != OK ||
                str_to_long_double(argv[5], &c) != OK) {
                printf("Error: one of the numbers is invalid\n");
                return INVALID_INPUT;
            }

            if (compare_with_epsilon(a, 0.0L, epsilon) &&
                compare_with_epsilon(b, 0.0L, epsilon) &&
                compare_with_epsilon(c, 0.0L, epsilon)) {
                printf("Error: all three arguments are equal to zero\n");
                return INVALID_INPUT;
            }
            else {
                ld arr[3] = {a, b, c};
                generate_permutations(a, b, c, epsilon, arr, 0);
            }
            break;

        case 'm':
            if (argc != 4) {
                printf("Error: not enough arguments.\n");
                return INVALID_INPUT;
            }
            long int number1, number2;

            if (str_to_int(argv[2], &number1) != OK ||
                str_to_int(argv[3], &number2) != OK || number1 == 0 || number2 == 0) {
                printf("Error: one of the numbers is invalid or equal to 0\n");
                return INVALID_INPUT;
            }
            if (number1 % number2 == 0) {
                printf("The number %ld is divisible by %ld without a remainder\n", number1, number2);
            } else {
                printf("The number %ld is not divisible by %ld without a remainder\n", number1, number2);
            }
            break;

        case 't':
            if (argc != 6) {
                printf("Error: not enough arguments.\n");
                return INVALID_INPUT;
            }
            ld eps, first, second, third;
            if (str_to_long_double(argv[2], &eps) != OK ||
                str_to_long_double(argv[3], &first) != OK ||
                str_to_long_double(argv[4], &second) != OK ||
                str_to_long_double(argv[5], &third) != OK) {
                printf("Error: one of the numbers is invalid\n");
                return INVALID_INPUT;
            }
            enum errors result = triangle(first, second, third, eps);
            if (result == INVALID_INPUT) {
                printf("Input error for sides\n");
                return INVALID_INPUT;
            } else if (result == ERROR_OVERFLOW) {
                printf("Error: memory overflow\n");
            }

            break;

        default:
            printf("Error: such a flag is not available: %s\n", argv[1]);
            break;
    }
    return 0;
}