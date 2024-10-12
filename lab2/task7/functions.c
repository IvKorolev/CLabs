#include "operations.h"

enum errors dihotomy(double *result, double left, double right, double epsilon, double(*func)(double)){
    double middle;
    if (func(left) * func(right) >= 0){
        return INVALID_INPUT;
    }
    if(epsilon <= 0)
    {
        return INVALID_INPUT;
    }
    while ((right - left) / 2 > epsilon){
        middle = (left + right) / 2;
        double res;
        res = func(middle);
        if (fabs(res) < epsilon){
            *result = middle;
            return OK;
        }
        if (res * func(left) < 0) {
            right = middle;
        }
        else {
            left = middle;
        }
    }
    *result = (left + right) / 2;
    return OK;
}

//x^2 - 4
double func1(double x){
    return x * x - 4;
}

//x - 2
double func2(double x){
    return -x + 2;
}

//x^2 - 2x = 1
double func3(double x){
    return x * x - 2 * x - 1;
}

//x^3 - 6x^2 + 9x - 4
double func4(double x){
    return x * x * x - 6 * x * x + 9 * x - 4;
}

//x^4 - 10x^3 + 35x^2 - 50x + 24
double func5(double x){
    return x * x * x * x - 10 * x * x * x + 35 * x * x - 50 * x + 25;
}

//x^2
double func6(double x){
    return x * x;
}