#include "operations.h"

int binomial_coeff(int n, int k) {
    if (k == 0 || k == n) return 1;
    int res = 1;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

enum errors polynomial_decomposition(double epsilon, double a, double **g, int degree, ...) {
    if (degree < 0) {
        *g = NULL;
        return INVALID_INPUT;
    }

    *g = (double *)malloc((degree + 1) * sizeof(double));
    if (*g == NULL) {
        return INVALID_MEMORY;
    }

    va_list args;
    va_start(args, degree);

    double *f = (double *)malloc((degree + 1) * sizeof(double));
    if (f == NULL){
        return INVALID_MEMORY;
    }
    for (int i = 0; i <= degree; i++) {
        f[i] = va_arg(args, double);
    }
    va_end(args);
    for (int i = 0; i <= degree; i++) {
        (*g)[i] = 0.0;
    }
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= i; j++) {
            (*g)[j] += f[i] * binomial_coeff(i, j) * pow(a, i - j);
        }
    }
    free(f);
    return OK;
}