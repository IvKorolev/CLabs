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

enum errors str_to_double(const char *x, double *res) {
    char symbol;
    if (sscanf(x, "%lf%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }

    if (*res >= DBL_MAX || *res <= DBL_MIN) {
        return INVALID_INPUT;
    }

    return OK;
}
double first_lim_e(double epsilon){
    int n = 1;
    double current = 0.0;
    double previous = 0.0;
    do{
        previous = current;
        current = pow((1.0 + 1.0 / n), n);
        n *= 2;
    }while(fabs(previous - current) > epsilon);
    return current;
}

double factorial(int n){
    if (n == 0 || n == 1) return 1.0;
    double result = 1.0;
    if (n > 20) n = 20;
    for (int i = 2; i < n; i++){
        result *= i;
    }
    return result;
}

double first_row_e(double epsilon){
    int n = 0;
    double current = 0.0;
    double temp;
    do{
        temp = 1.0 / (factorial(n));
        current += temp;
        n += 1;
    }while(temp > epsilon);
    return current;
}

double first_equation_e(double epsilon){
    double x = 3.0;
    double f = 1.0, df;
    while(fabs(f) > epsilon){
        f = log(x) - 1;
        df = 1.0 / x;
        x = x - f / df;
    }
    return x;
}

double second_lim_pi(double epsilon){
    int n = 2;
    double current = 4.0, previous = 0;
    do
    {
        previous = current;
        current *= (4.0 * n * ( n - 1.0)) / pow(2.0 * n - 1.0, 2);
        n++;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double second_row_pi(double epsilon){
    int n = 1;
    double temp, current = 0.0;
    do{
        temp = pow(-1.0, n - 1) / (2*n - 1);
        current += temp;
        n += 1;
    }while(fabs(temp) > epsilon);
    return 4 * current;
}

double second_equation_pi(double epsilon){
    double x = 3.0;
    double f = 1.0, df;
    while (fabs(f) > epsilon)
    {
        f = cos(x) + 1.0;
        df = -sin(x);
        x = x - f / df;
    }
    return x;
}

double third_limit_ln(double epsilon){
    int n = 1;
    double current = 0.0, previous;
    do{
        previous = current;
        current = n * (pow(2.0, 1.0 / n) - 1);
        n += 1;
    }while(fabs(current - previous) > epsilon);
    return current;
}

double third_row_ln(double epsilon){
    int n = 1;
    double current = 0.0, temp;
    do{
        temp = (n % 2 == 1 ? 1.0 : -1.0) / n;
        current += temp;
        n += 1;
    }while(fabs(temp) > epsilon);
    return current;
}

double third_equation_ln(double epsilon){
    double x = 1.0;
    double f = 1.0, df;
    while(fabs(f) > epsilon){
        f = exp(x) - 2;
        df = exp(x);
        x = x - f / df;
    }
    return x;
}

double fourth_lim_sqrt(double epsilon){
    double previous = 0, current = -0.5;
    do{
        previous = current;
        current = previous - pow(previous, 2) / 2 + 1;
    }while(fabs(current - previous) > epsilon);
    return current;
}

double fourth_row_sqrt(double epsilon){
    int k = 2;
    double current = 1.0, previous, temp;
    do{
        previous = current;
        double temp1 = pow(2.0, -k);
        temp = pow(2.0, temp1);
        current *= temp;
    }while(fabs(current - previous) > epsilon);
    return current;
}

double fourth_equation_sqrt(double epsilon){
    double x = 1.0;
    double f = 1.0, df;
    while(fabs(f) > epsilon){
        f = pow(x, 2.0) - 2;
        df = 2 * x;
        x = x - f / df;
    }
    return x;
}

double C(double m, double k){
    if (k > m || m < 0) return 0.0;
    double chisl = factorial(m);
    double znam = factorial(k) * factorial(m - k);
    return chisl / znam;
}

double fifth_lim_gamma(double epsilon){
    int m = 1;
    double current = 0.0, previous;
    do{
        previous = current;
        current = 0.0;
        for (int k = 1; k < m; k++){
            current += C(m, k) * (pow(-1, k) / k) * log(factorial(k));
        }
        m += 1;
    }while(fabs(current - previous) > epsilon);
    return current;
}

double fifth_row_gamma(double epsilon){
    double sum = -M_PI * M_PI / 6.0;
    double k = 2.0;
    double current = 0.0, previous;
    do{
        previous = current;
        int sqrt_k = (int)sqrt(k);
        current += (1.0 / (sqrt_k * sqrt_k)) - (1.0 / k);
        k += 1;
    }while(fabs(current - previous) > epsilon);
    return current;
}

int is_prime(int x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    for (int i = 3; i <= floor(sqrt(x)); i += 2){
        if (x % i == 0){
            return 0;
        }
    }
    return 1;
}

double fifth_equation_gamma(double epsilon) {
    int p = 2;
    double current = log(2) * 0.5;
    double previous = 0;
    double proizved = 1.0;
    do {
        previous = current;
        do{
            p++;
        }while (!is_prime(p));
        proizved *= (p - 1.0) / p;
        current = log(p) + proizved;
    }while (fabs(previous - current) >= epsilon);
    return -log(current);
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Неправильное количество аргументов\n");
        return INVALID_INPUT;
    }
    double epsilon;
    if(str_to_double(argv[1], &epsilon) != OK || epsilon <= 0)
    {
        printf("Некорректный ввод epsilon\n");
        return INVALID_INPUT;
    }

    double results[15];
    results[0] = first_lim_e(epsilon);
    results[1] = second_lim_pi(epsilon);
    results[2] = third_limit_ln(epsilon);
    results[3] = fourth_lim_sqrt(epsilon);
    results[4] = fifth_lim_gamma(epsilon);

    results[5] = first_row_e(epsilon);
    results[6] = second_row_pi(epsilon);
    results[7] = third_row_ln(epsilon);
    results[8] = fourth_row_sqrt(epsilon);
    results[9] = fifth_row_gamma(epsilon);

    results[10] = first_equation_e(epsilon);
    results[11] = second_equation_pi(epsilon);
    results[12] = third_equation_ln(epsilon);
    results[13] = fourth_equation_sqrt(epsilon);
    results[14] = fifth_equation_gamma(epsilon);

    char* constants[5] = {"e", "pi", "ln2", "sqrt2", "gamma"};
    char* ways[3] = {"LIMITS", "ROWS","EQUATIONS"};

    int precision = 0;
    double temp = epsilon;
    while (temp != 1)
    {
        temp *= 10;
        ++precision;
    }
    for(int i = 0; i < 15; i++){
        if(i%5 == 0){
            printf("\n %6c%s", ' ', ways[i/5]);
        }
        printf("\nresult for %s:", constants[i%5]);
        if (results[i] != INFINITY && !isnan(results[i])) {
            printf(" %.*f", precision, results[i]);
        } else {
            printf(" couldn't calculate constant with given accuracy");
        }
    }

    return 0;
}
