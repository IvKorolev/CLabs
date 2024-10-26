#include "operations.h"

int main(int argc, char* argv[]){

    if (argc != 3) {
        printf("Ошибка. Неправильное количество аргументов\n");
        return INVALID_INPUT;
    }
    FILE* result = fopen(argv[2], "w");
    FILE* input_file = fopen(argv[1], "r");
    if (result == NULL || input_file == NULL){
        printf("Ошибка открытия одного из файлов\n");
        if (input_file != NULL) fclose(input_file);
        if (result != NULL) fclose(result);
        return INVALID_MEMORY;
    }
    enum errors status = first(input_file, result);
    if (status != OK){
        printf("\n");
        fclose(input_file);
        fclose(result);
        return INVALID_INPUT;
    }
    fclose(input_file);
    fclose(result);
    return 0;
}