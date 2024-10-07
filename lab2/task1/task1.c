#include "operations.h"

int main(int argc, char* argv[]){
    if (argv[1][0] != '-' && (argv[1][2] == '\0')){
        printf("Ошибка ввода флага\n");
        return INVALID_INPUT;
    }
    switch(argv[1][1]){
        case 'l':
            if (argc < 3){
                printf("Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            printf("%d\n", string_length(argv[2]));
            break;
        case 'r':
            if (argc < 3){
                printf("Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            char* reversed_str;
            if (reverse_str(argv[2], &reversed_str) != OK){
                printf("Ошибка выделения памяти\n");
                return INVALID_MEMORY;
            }
            printf("%s\n", reversed_str);
            free(reversed_str);
            break;
        case 'u':
            if (argc < 3){
                printf("Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            char* resultu;
            if(high_register(argv[2], &resultu) != OK){
                printf("Ошибка выделения памяти\n");
                return INVALID_INPUT;
            }
            printf("%s\n", resultu);
            free(resultu);
            break;
        case 'n':
            if (argc < 3){
                printf("Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            char* resultn;
            if (new_str(argv[2], &resultn) != OK){
                printf("Ошибка выделения памяти\n");
                return INVALID_MEMORY;
            }
            printf("%s\n", resultn);
            free(resultn);
            break;
        case 'c':
            if (argc < 4){
                printf("Неправильное количество аргументов\n");
                return INVALID_INPUT;
            }
            int count_str = argc - 3;
            long int res;
            if (str_to_int(argv[2], &res) != OK){
                printf("Ошибка ввода 3 аргумента\n");
                return INVALID_INPUT;
            }
            char* resultc;
            if(concatenate_all((argv + 3), count_str, &resultc, res) != OK)
            {
                printf("Ошибка выделения памяти\n");
                return INVALID_MEMORY;
            }
            printf("%s\n", resultc);
            free(resultc);
            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            break;
    }
    return 0;
}