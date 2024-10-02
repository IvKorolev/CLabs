#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

void first(FILE* input1, FILE* input2, FILE* output){
    char symbol1[100], symbol2[100];
    int read1, read2;
    while (1) {
        read1 = fscanf(input1, "%s", symbol1);
        read2 = fscanf(input2, "%s", symbol2);

        if (read1 != EOF) {
            fprintf(output, "%s ", symbol1);
        }
        if (read2 != EOF) {
            fprintf(output, "%s ", symbol2);
        }

        if (read1 == EOF && read2 == EOF) {
            break;
        }
    }
}

void process_lexeme(char* lexeme, int position, FILE* output) {
    if (position % 10 == 0) {
        for (int i = 0; lexeme[i] != '\0'; i++) {
            char lower_char = tolower(lexeme[i]);
            fprintf(output, "%ld ", strtol((char[2]){lower_char, '\0'}, NULL, 4));
        }
    }
    else if (position % 5 == 0){
        for (int i = 0; lexeme[i] != '\0'; i++) {
            fprintf(output, "%o ", lexeme[i]);
        }
    }
    else if (position % 2 == 0){
        for (int i = 0; lexeme[i] != '\0'; i++) {
            fprintf(output, "%c", tolower(lexeme[i]));
        }
        fprintf(output, " ");
    }
    else{
        fprintf(output, "%s ", lexeme);
    }
}

const char* get_filename(const char* path) {
    const char* last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        return last_slash + 1;
    }
    return path;
}

void second(FILE* input, FILE* output) {
    char lexeme[100];
    int position = 1;
    while (fscanf(input, "%s", lexeme) != EOF){
        process_lexeme(lexeme, position, output);
        position++;
    }
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Неправильное количество аргументов\n");
        return INVALID_INPUT;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/'){
        printf("Флаг должен начинаться с - или /\n");
        return INVALID_INPUT;
    }

    switch(argv[1][1]){
        case 'r':
            if (argc != 5){
                printf("Ошибка. Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            FILE* input1 = fopen(argv[2], "r");
            FILE* input2 =  fopen(argv[3], "r");
            FILE* output =  fopen(argv[4], "w");
            if (input1 == NULL || input2 == NULL || output == NULL){
                fclose(input1);
                fclose(input2);
                fclose(output);
                printf("Ошибка открытия одного из файлов\n");
                return INVALID_MEMORY;
            }
            const char* rinput_filename1 = get_filename(argv[2]);
            const char* rinput_filename2 = get_filename(argv[3]);
            const char* routput_filename = get_filename(argv[4]);

            if (strcmp(rinput_filename1, routput_filename) == 0) {
                printf("Ошибка: входной и выходной файлы имеют одинаковые имена\n");
                return INVALID_INPUT;
            }
            if (strcmp(rinput_filename2, routput_filename) == 0) {
                printf("Ошибка: входной и выходной файлы имеют одинаковые имена\n");
                return INVALID_INPUT;
            }
            first(input1, input2, output);
            fclose(input1);
            fclose(input2);
            fclose(output);
            break;
        case 'a':
            if (argc != 4){
                printf("Ошибка. Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            FILE* input = fopen(argv[2], "r");
            FILE* output_a = fopen(argv[3], "w");
            if (input == NULL || output_a == NULL) {
                fclose(input);
                fclose(output_a);
                printf("Ошибка открытия одного из файлов\n");
                return INVALID_MEMORY;
            }
            const char* ainput_filename1 = get_filename(argv[2]);
            const char* aoutput_filename = get_filename(argv[3]);
            if (strcmp(ainput_filename1, aoutput_filename) == 0) {
                printf("Ошибка: входной и выходной файлы имеют одинаковые имена\n");
                return INVALID_INPUT;
            }
            second(input, output_a);
            fclose(input);
            fclose(output_a);
            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            break;
    }

    return 0;
}