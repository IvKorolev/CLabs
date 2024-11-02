#include "operations.h"

int main(int argc, char* argv[]) {
    char* base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int count;

    for (int r = 1; r <= 5; r = sum(r, 1)){

        int capacity = 1;
        int flag_negative = 0;

        char* result = (char*)malloc(multiply(sizeof(char), capacity));
        if (result == NULL)
        {
            printf("Ошибка выделения памяти\n");
            return INVALID_MEMORY;
        }

        if(first(154, r, &result, &capacity, &count, base, &flag_negative) != OK)
        {
            printf("Ошибка ввода\n");
            free(result);
            return INVALID_INPUT;
        }

        print_num(flag_negative, result, count, r);
        flag_negative = 0;
        free(result);
    }
    return 0;
}