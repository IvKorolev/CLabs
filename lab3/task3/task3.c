#include "operations.h"

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("Ошибка. Неправильное количество аргументов\n");
        return INVALID_INPUT;
    }
    if (argv[2][0] != '/' && argv[2][0] != '-'){
        printf("Ошибка ввода флага. Он должен начинаться с / или -\n");
        return INVALID_INPUT;
    }
    if (compare_files(argv[1], argv[3])){
        printf("Ошибка: входной и выходной файлы имеют одинаковые имена\n");
        return INVALID_INPUT;
    }
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[3], "w");
    if (input == NULL || output == NULL){
        if (input != NULL) fclose(input);
        if (output != NULL) fclose(output);
        printf("Ошибка открытия одного из файлов\n");
        return INVALID_INPUT;
    }
    Employee* result = NULL;
    int size = 0;
    create_list(input, &result, &size);
    switch(argv[2][1]){
        case 'a':
            qsort(result, size, sizeof(Employee), compare_ascending);
            for (int i = 0; i < size; i++){
                fprintf(output, "%d %s %s %lf\n", result[i].id, result[i].name, result[i].last_name, result[i].payment);
            }
            break;
        case 'd':
            qsort(result, size, sizeof(Employee), compare_descending);
            for (int i = 0; i < size; i++){
                fprintf(output, "%d %s %s %lf\n", result[i].id, result[i].name, result[i].last_name, result[i].payment);
            }
            break;
        default:
            printf("Такого флага нет в доступных\n");
            break;
    }
    free(result);
    fclose(input);
    fclose(output);
    return 0;
}