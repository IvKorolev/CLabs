#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h>

enum errors {
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

enum errors validate_input(const char *str, int base) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            if (!isupper(str[i]) || (str[i] - 'A' + 10 >= base)) {
                return INVALID_INPUT;
            }
        }
        else if (isdigit(str[i])){
            if (str[i] - '0' >= base){
                return INVALID_INPUT;
            }
        }
        else{
            return INVALID_INPUT;
        }
    }
    return OK;
}

enum errors convert_to_base(long long int num, int base, char *output, size_t size) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[100];
    int index = 0;

    if (num == 0) {
        snprintf(output, size, "0");
        return OK;
    }

    long long int abs_num = llabs(num);

    while (abs_num > 0) {
        if (index >= sizeof(buffer) - 1) {
            return INVALID_MEMORY;
        }
        buffer[index++] = digits[abs_num % base];
        abs_num /= base;
    }

    buffer[index] = '\0';

    int start = 0;
    if (num < 0) {
        if (size <= 1) {
            return INVALID_MEMORY;
        }
        output[0] = '-';
        start = 1;
    }

    for (int i = 0; i < index; i++) {
        if (start + i >= size - 1) {
            return INVALID_MEMORY;
        }
        output[start + i] = buffer[index - i - 1];
    }
    output[start + index] = '\0';

    return OK;
}

int main() {
    char input[100];
    int base;
    long long int max_value = 0;
    long long int current_value;
    char *endptr, max_result[100];
    char result[100];

    scanf("%d", &base);

    if (base < 2 || base > 36) {
        printf("Ошибка ввода, система счисления должна быть от 2 до 36\n");
        return 1;
    }

    while (1) {
        scanf("%s", input);

        if (strcmp(input, "Stop") == 0) {
            break;
        }

        if (validate_input(input, base) != OK) {
            printf("Ошибка: число содержит некорректные символы\n");
            return INVALID_INPUT;
        }

        current_value = strtoll(input, &endptr, base);

        if (*endptr != '\0' || (current_value == LLONG_MAX || current_value == LLONG_MIN)) {
            printf("Ошибка: число слишком большое для обработки или недопустимо\n");
            return INVALID_INPUT;
        }

        if (llabs(current_value) > llabs(max_value)) {
            max_value = current_value;
            strcpy(max_result, input);
        }
    }

    printf("Максимальное число по модулю: %s\n", max_result);

    for (int i = 9; i <= 36; i+= 9){
        if(convert_to_base(max_value, i, result, sizeof(result)) == OK){
            printf("В системе счисления с основанием %d: %s\n", i, result);
        }else{
            printf("Ошибка памяти при преобразовании числа в систему счисления %d\n", i);
        }
    }
    return 0;
}
