#include "operations.h"

int main(int argc, char* argv[]){
    double epsilon = 0.0001;
    double result;
    enum errors status = dihotomy(&result, 1, 3, epsilon, func2);
    if(status == OK){
        printf("%lf\n", result);
    }
    else{
        printf("Ошибка ввода, результаты функции должны иметь разные знаки и епсилон должен быть больше нуля\n");
    }
    return 0;
}