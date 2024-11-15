#include "operations.h"

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Ошибка, неправильный ввод\n");
        return INVALID_INPUT;
    }

    MemoryCell** Allcells = NULL;
    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Ошибка открытия файла\n");
        return INVALID_MEMORY;
    }
    enum errors result = process_file(input, &Allcells);
    fclose(input);

    if (result != OK){
        printf("Ошибка обработки файла\n");
    }

    return 0;
}