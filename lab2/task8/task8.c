#include "operations.h"

int main(int argc, char* argv[]){
    char *result;
    enum errors status = first(&result, 13, 3, "AA", "AB", "CA");
    if (status == INVALID_INPUT){
        printf("Ошибка ввода системы счисления или чисел\n");
        return INVALID_INPUT;
    }
    else if(status == INVALID_MEMORY){
        printf("Ошибка памяти\n");
    }
    else{
        printf("%s\n", result);
    }
    free(result);
    return 0;
}