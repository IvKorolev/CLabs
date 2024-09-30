#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

enum errors {
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

int find_min_base(const char *str) {
    int min_base = 2;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = toupper(str[i]);
        if (isdigit(c)) {
            int digit = c - '0';
            if (digit >= min_base) {
                min_base = digit + 1;
            }
        } else if (isalpha(c)) {
            int digit = c - 'A' + 10;
            if (digit >= min_base) {
                min_base = digit + 1;
            }
        }
    }
    return min_base;
}

enum errors convert_to_decimal(const char *str, int base, long long int *result) {
    char *endptr;
    *result = strtoll(str, &endptr, base);
    if (*endptr != '\0' || (*result == LLONG_MAX || *result == LLONG_MIN)) {
        return INVALID_INPUT;
    }
    return OK;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Ошибка: некорректное количество аргументов\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Ошибка чтения входного файла\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Ошибка открытия выходного файла\n");
        fclose(input);
        return 1;
    }

    char word[100];
    while (fscanf(input, "%s", word) == 1) {
        int min_base = find_min_base(word);

        long long int decimal_value;
        if ((convert_to_decimal(word, min_base, &decimal_value) != OK)){
            printf("Ошибка: число слишком большое для обработки или недопустимо\n");
            return INVALID_INPUT;
        }

        fprintf(output, "%s %d %lld\n", word, min_base, decimal_value);
    }

    fclose(input);
    fclose(output);

    return 0;
}
