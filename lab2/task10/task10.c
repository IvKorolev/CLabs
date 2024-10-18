#include "operations.h"

int main() {
    double *g = NULL;

    //f(x) = 2 + 3x + x^2 a = 1
    int degree = 2;
    enum errors status = polynomial_decomposition(1e-6, 1.0, &g, degree, 2.0, 3.0, 1.0);

    //f(x) = 4 + 2x + x^3 a = 2
//    int degree = 3;
//    enum errors status = polynomial_decomposition(1e-6, 2.0, &g, degree, 4.0, 2.0, 0.0, 1.0);

    //f(x) = 1 - x + x^2 a = -1
//    int degree = 2;
//    enum errors status = polynomial_decomposition(1e-6, -1.0, &g, degree, 1.0, -1.0, 1.0);

    //f(x) = 1 - 4x + 6x^2 - 4x^3 + x^4 a = -0
//    int degree = 4;
//    enum errors status = polynomial_decomposition(1e-6, 0.0, &g, degree, 1.0, -4.0, 6.0, -4.0, 1.0);

    if (status == OK){
        for (int i = 0; i <= degree; i++) {
            printf("g[%d] = %f\n", i, g[i]);
        }
    }
    else if (status == INVALID_INPUT){
        printf("Ошибка ввода\n");
        free(g);
        return INVALID_INPUT;
    }
    else{
        printf("Ошибка памяти\n");
        free(g);
        return INVALID_MEMORY;
    }

    free(g);
    return 0;
}