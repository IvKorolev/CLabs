#include "operations.h"

enum errors reverse_str(const char* str, char** res){
    int length = strlen(str);
    (*res) = (char*)malloc(sizeof(char) * (length + 1));
    if (*res == NULL){
        free(res);
        return INVALID_MEMORY;
    }
    int i = 0;
    --length;
    while(length >= 0)
    {
        (*res)[i++] = str[length--];
    }
    (*res)[i] = '\0';
    return OK;
}

enum errors sum_nums(const char* num1, const char* num2, int base, char** result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;

    *result = (char*)malloc(max_len + 2);
    if (*result == NULL) {
        return INVALID_MEMORY;
    }
    int carry = 0;
    int i1 = len1 - 1, i2 = len2 - 1, res_idx = 0;
    while (i1 >= 0 || i2 >= 0 || carry) {
        char digit_str[2] = {0, 0};

        if (i1 >= 0) {
            digit_str[0] = num1[i1];
        } else {
            digit_str[0] = '0';
        }
        int digit1 = strtol(digit_str, NULL, base);

        if (i2 >= 0) {
            digit_str[0] = num2[i2];
        }
        else {
            digit_str[0] = '0';
        }
        int digit2 = strtol(digit_str, NULL, base);

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        sum = sum % base;

        snprintf(digit_str, 2, "%X", sum);
        (*result)[res_idx++] = digit_str[0];

        i1--;
        i2--;
    }

    (*result)[res_idx] = '\0';

    char* temp;
    reverse_str(*result, &temp);
    free(*result);
    *result = temp;

    return OK;
}

enum errors first(char ** result, int base, int count, ...) {
    if (base < 2 || base > 36 || count <= 0) {
        return INVALID_INPUT;
    }

    va_list arguments;
    va_start(arguments, count);

    char* current_sum = va_arg(arguments, char*);

    for (int i = 0; i < strlen(current_sum); i++) {
        if (strtol((char[]){current_sum[i], 0}, NULL, base) >= base) {
            va_end(arguments);
            return INVALID_INPUT;
        }
    }

    for (int i = 1; i < count; i++) {
        char* str = va_arg(arguments, char*);

        for (int j = 0; j < strlen(str); j++) {
            if (strtol((char[]){str[j], 0}, NULL, base) >= base) {
                va_end(arguments);
                return INVALID_INPUT;
            }
        }

        char* new_sum;
        enum errors status = sum_nums(current_sum, str, base, &new_sum);
        if (status != OK) {
            va_end(arguments);
            return status;
        }
        current_sum = new_sum;
    }

    va_end(arguments);

    while (*current_sum == '0' && *(current_sum + 1) != '\0') {
        current_sum++;
    }

    *result = current_sum;
    return OK;
}