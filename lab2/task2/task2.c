#include "operations.h"

int main(int argc, char* argv[]){
    int count = 5;
    double result;
    enum errors res_1 = first(&result, count, 1.0, 1.2, 1.3, 1.4, 1.5);
    if(res_1 == OK){
        printf("%lf\n", result);
    }
    else if(res_1 == INVALID_INPUT){
        printf("Ошибка ввода количества аргументов\n");
    }
    else{
        printf("Ошибка. Произошло переполнение\n");
    }
    return 0;
}