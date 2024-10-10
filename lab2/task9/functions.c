#include "operations.h"

void get_prime_factors(int base, int factors[], int *factor_count) {
    int i = 2;
    *factor_count = 0;

    while (base > 1) {
        if (base % i == 0) {
            factors[(*factor_count)++] = i;
            base /= i;
        } else {
            i++;
        }
    }
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void convert_to_fraction(double fraction, int *numerator, int *denominator) {
    *denominator = 1;
    while (fraction-(int)fraction != 0) {
        fraction *= 10;
        *denominator *= 10;
    }
    *numerator = (int)fraction;

    int common_divisor = gcd(*numerator, *denominator);
    *numerator /= common_divisor;
    *denominator /= common_divisor;
}

int has_finite_representation(int denominator, int factors[], int factor_count) {
    for (int i = 0; i < factor_count; i++) {
        while (denominator % factors[i] == 0) {
            denominator /= factors[i];
        }
    }
    return denominator == 1;
}

void print_check_infinite_representation(int count, int base, ...) {

    int factors[20];
    int factor_count;
    get_prime_factors(base, factors, &factor_count);

    va_list args;
    va_start(args, base);

    for (int i = 0; i < count; i++) {
        double fraction = va_arg(args, double);
        int numerator, denominator;

        convert_to_fraction(fraction, &numerator, &denominator);

        if (has_finite_representation(denominator, factors, factor_count)) {
            printf("Дробь имеет конечное представление в системе с основанием %d\n", base);
        } else {
            printf("Дробь имеет бесконечное представление в системе с основанием %d\n", base);
        }
    }

    va_end(args);
}