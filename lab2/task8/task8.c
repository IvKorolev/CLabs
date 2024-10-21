#include "operations.h"

int main(int argc, char* argv[]){
    char *result;
    enum errors status = first(&result, 14, 3, "00000000000000000000000CC", "A", "0000000000000");
    if (status == INVALID_INPUT){
        printf("Ошибка ввода системы счисления или чисел\n");
        return INVALID_INPUT;
    }
    else if(status == INVALID_MEMORY){
        printf("Ошибка памяти\n");
        return INVALID_MEMORY;
    }
    else{
        printf("%s\n", result);
    }
    free(result);
    return 0;
}