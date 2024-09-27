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
    for (int i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

double first_row_e(double epsilon){
    int n = 1;
    double current = 1.0;
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
        k += 1;
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

double C(int m, int k){
    if (k > m || m < 0) return 0.0;
    double chisl = factorial(m);
    double znam = factorial(k) * factorial(m - k);
    return chisl / znam;
}

double fifth_lim_gamma(double epsilon){
    int m = 1;
    double current = 0.0, previous = 0.0;
    do{
        previous = current;
        current = 0.0;
        for (int k = 1; k <= m; k++){
            current += C(m, k) * (pow(-1, k) / k) * log(factorial(k));
        }
        m += 1;
    }while(fabs(current - previous) > epsilon);
    return current;
}

double fifth_row_gamma(double epsilon){
    int k = 2;
    double current = 0.0, previous = 0.0;
    double l = 0;
    do{
        previous = current;
        l = sqrt(k);
        if (fmod(l,1.0) == 0)
        {
            k +=
                    1;
            l = (int)pow(k, 1.0/2.0);
        }
        current += (1.0 / pow((int)l, 2.0)) - (1.0 / k);
        k += 1;
    }while(fabs(current - previous) > epsilon);
    return current - pow(M_PI, 2)/6;
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
        printf("Ошибка ввода epsilon\n");
        return INVALID_INPUT;
    }
    printf("--------Limit---------\n");
    printf("e:   %.15f\n", first_lim_e(epsilon));
    printf("π:   %.15f\n", second_lim_pi(epsilon));
    printf("ln2: %.15f\n", third_limit_ln(epsilon));
    printf("√2:  %.15f\n", fourth_lim_sqrt(epsilon));
    printf("Ɣ:   %.15f\n", fifth_lim_gamma(epsilon));
    printf("---------Rows---------\n");
    printf("e:   %.15f\n", first_row_e(epsilon));
    printf("π:   %.15f\n", second_row_pi(epsilon));
    printf("ln2: %.15f\n", third_row_ln(epsilon));
    printf("√2:  %.15f\n", fourth_row_sqrt(epsilon));
    printf("Ɣ:   %.15f\n", fifth_row_gamma(epsilon));
    printf("-------Equation-------\n");
    printf("e:   %.15f\n", first_equation_e(epsilon));
    printf("π:   %.15f\n", second_equation_pi(epsilon));
    printf("ln2: %.15f\n", third_equation_ln(epsilon));
    printf("√2:  %.15f\n", fourth_equation_sqrt(epsilon));
    printf("Ɣ:   %.15f\n", fifth_equation_gamma(epsilon));
    return 0;
}