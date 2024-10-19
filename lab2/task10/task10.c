#include "operations.h"

int main() {
    double *g = NULL;
    double *g1 = NULL;

    //f(x) = 2 + 3x + x^2 a = 1
    int degree = 2;
    enum errors status = polynomial_decomposition(1e-6, 1.0, &g, degree, 2.0, 3.0, 1.0);
    enum errors status1 = polynomial_decomposition(1e-6, 2.0, &g1, degree, 2.0, 3.0, 1.0);

    //f(x) = 4 + 2x + x^3 a = 2
//    int degree = 3;
//    enum errors status = polynomial_decomposition(1e-6, 2.0, &g, degree, 4.0, 2.0, 0.0, 1.0);

    //f(x) = 1 - x + x^2 a = -1
//    int degree = 2;
//    enum errors status = polynomial_decomposition(1e-6, -1.0, &g, degree, 1.0, -1.0, 1.0);

    //f(x) = 1 - 4x + 6x^2 - 4x^3 + x^4 a = -0
//    int degree = 4;
//    enum errors status = polynomial_decomposition(1e-6, 0.0, &g, degree, 1.0, -4.0, 6.0, -4.0, 1.0);
    double result_f;
    double result_g;
    for (int i = 1; i <= 3; i++){
        result_f = 2 + 3 * i + pow(i,2);
        enum errors status_i = polynomial_decomposition(1e-6, 1.0, &g, degree, 2.0, 3.0, 1.0);
        if (status_i == OK){
            result_g = g[2] * pow(i - 1.0, 2) + g[1] * (i - 1.0) + g[0];
            printf("Result for f(%d): %f\n", i, result_f);
            printf("Result for g(%d): %f\n", i, result_g);
        }
    }
//    if (status == OK){
//        for (int i = 0; i < degree; i++) {
//            printf("g[%d] = %f\n", i, g[i]);
//
//            printf("%d");
//        }
//    }
//    else if (status == INVALID_INPUT){
//        printf("Ошибка ввода\n");
//        free(g);
//        return INVALID_INPUT;
//    }
//    else{
//        printf("Ошибка памяти\n");
//        free(g);
//        return INVALID_MEMORY;
//    }

    free(g);
    return 0;
}