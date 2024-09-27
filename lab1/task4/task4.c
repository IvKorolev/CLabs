#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

enum errors erase_nums(FILE* input, FILE* output){
    char symbol;
    while ((symbol = fgetc(input)) != EOF){
        if (!isdigit(symbol)){
            fputc(symbol, output);
        }
    }
    return OK;
}

enum errors count_letters(FILE* input, FILE* output){
    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), input)){
        int count = 0;
        for (int i = 0; buffer[i]; i++){
            if (isalpha(buffer[i])){
                count++;
            }
        }
        fprintf(output, "Кол-во латинских букв: %d\n", count);
    }
    return OK;
}

enum errors count_special_symbols(FILE* input, FILE* output){
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)){
        int count = 0;
        for (int i = 0; buffer[i]; ++i){
            if (!isalnum(buffer[i]) && buffer[i] != ' '){
                count++;
            }
        }
        fprintf(output, "Количество специальных символов: %d\n", count);
    }
    return OK;
}

enum errors replace_ascii(FILE* input, FILE* output){
    char symbol;
    while ((symbol = fgetc(input)) != EOF){
        if (isdigit(symbol)){
            fputc(symbol, output);
        }
        else{
            fprintf(output, "%02X", (unsigned char)symbol);
        }
    }
    return OK;
}

int main(int argc, char* argv[]){

    if (argc < 3){
        printf("Неправильное количество аргументов\n");
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '/' || argv[1][0] == '-') && (argv[1][2] == '\0' || argv[1][3] == '\0'))){
        printf("Ошибка ввода флага\n");
        return INVALID_INPUT;
    }

    FILE* input = fopen(argv[2], "r");
    if (input == NULL){
        printf("Ошибка чтения первого файла\n");
        return INVALID_INPUT;
    }

    FILE* output = NULL;
    char* output_name = NULL;

    if (argv[1][1] == 'n'){
        if (argc != 4){
            printf("Неправильное количество аргументов\n");
            fclose(input);
            return INVALID_INPUT;
        }
        output_name = argv[3];
    }
    else{
        if (argc != 3){
            printf("Неправильное количество аргументов\n");
            fclose(input);
            return INVALID_INPUT;
        }

        output_name = malloc((strlen(argv[2]) + strlen("/out_") + 1) * sizeof(char));
        if (output_name == NULL){
            printf("Ошибка выделения памяти\n");
            fclose(input);
            return INVALID_MEMORY;
        }

        char* last_slash = strrchr(argv[2], '/');
        if (last_slash){
            strncpy(output_name, argv[2], last_slash - argv[2] + 1);
            output_name[last_slash - argv[2] + 1] = '\0';
            strcat(output_name, "out_");
            strcat(output_name, last_slash + 1);
        }
        else{
            strcpy(output_name, "out_");
            strcat(output_name, argv[2]);
        }
    }

    output = fopen(output_name, "w");
    if (output == NULL){
        printf("Ошибка открытия файла %s\n", output_name);
        fclose(input);
        if (argv[1][1] != 'n') free(output_name);
        return INVALID_INPUT;
    }

    if (argv[1][1] != 'n'){
        free(output_name);
    }

    int length = strlen(argv[1]);
    switch (argv[1][length - 1]){
        case 'd':
            erase_nums(input, output);
            break;
        case 'i':
            count_letters(input, output);
            break;
        case 's':
            count_special_symbols(input, output);
            break;
        case 'a':
            replace_ascii(input, output);
            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            fclose(input);
            fclose(output);
            return INVALID_INPUT;
    }

    fclose(input);
    fclose(output);

    return 0;
}
