#include "operations.h"

int main(int argc, char* argv[]){
    char *result;
    enum errors status = first(&result, 16, 3, "A", "F", "CA");
    if (status == INVALID_INPUT){
        printf("Ошибка ввода системы счисления или чисел\n");
        free(result);
        return INVALID_INPUT;
    }
    else if(status == INVALID_MEMORY){
        printf("Ошибка памяти\n");
        free(result);
        return INVALID_MEMORY;
    }
    else{
        printf("%s\n", result);
    }
    free(result);
    return 0;
}