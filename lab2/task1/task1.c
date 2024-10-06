#include "operations.h"

int main(int argc, char* argv[]){
    if (argv[1][0] != '-' && (argv[1][2] == '\0')){
        printf("Ошибка ввода флага\n");
        return INVALID_INPUT;
    }
    switch(argv[1][1]){
        case 'l':
            break;
        case 'r':
            break;
        case 'u':
            break;
        case 'n':
            break;
        case 'c':
            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            break;
    }
    return 0;
}