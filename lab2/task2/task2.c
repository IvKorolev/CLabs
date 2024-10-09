#include "operations.h"

int main(int argc, char* argv[]){
    int count = 5;
    double result1;
    enum errors status1 = first(&result1, count, 1.0, 1.2, 1.3, 1.4, 1.5);
    if(status1 == OK){
        printf("%lf\n", result1);
    }
    else if(status1 == INVALID_INPUT){
        printf("Ошибка ввода количества аргументов\n");
    }
    else{
        printf("Ошибка. Произошло переполнение\n");
    }
    double result2;
    enum errors status2 = second(2, 3, &result2);
    if (status2 == OK){
        printf("%lf\n", result2);
    }
    else if(status2 == INVALID_INPUT){
        printf("Ошибка ввода\n");
    }
    else{
        printf("Ошибка. Произошло переполнение\n");
    }
    return 0;
}