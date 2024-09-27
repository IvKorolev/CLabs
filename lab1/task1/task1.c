#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

enum errors str_to_int(const char *x, long int *res) {
    char symbol;
    if (sscanf(x, "%ld%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }

    if (abs(*res) >= INT_MAX || abs(*res) <= INT_MIN) {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors natural_to_100(long int x, int** result, int* size){
    if (x == 0){
        return INVALID_INPUT;
    }
    int capacity = 4;
    *result = (int*)malloc(capacity * sizeof(int));
    if (result == NULL){
        return INVALID_MEMORY;
    }
    for (int i = 1; i <= 100; i++){
        if(i % x == 0){
            (*result)[(*size)++] = i;
            if (capacity == *size) {
                capacity *= 2;
                int *new_memory = realloc(*result, capacity * sizeof(int));
                if (new_memory == NULL){
                    return INVALID_MEMORY;
                }
                *result = new_memory;
            }
        }
    }
    return OK;
}

int is_prime(long int x){
    if (x < 0){
        x *= -1;
    }
    if (x == 0 || x == 1){
        return 0;
    }
    if (x == 2){
        return 1;
    }
    if (x % 2 == 0) return 0;
    for (int i = 3; i <= floor(sqrt(x)); i += 2){
        if (x % i == 0){
            return 0;
        }
    }
    return 1;
}

enum errors divide_to_nums(long int x, char** result, int* size, int* flag){
    if (x < 0){
        *flag = 1;
        x *= -1;
    }
    int capacity = 4;
    *result = (char*)malloc(capacity * sizeof(char));
    if (*result == NULL) return INVALID_MEMORY;
    int temp = 0;
    while (x > 0){
        temp = x % 16;
        if (temp < 10){
            (*result)[(*size)++] = temp + '0';
        }
        else {
            (*result)[(*size)++] = temp - 10 + 'A';
        }
        x /= 16;
        if (capacity == *size){
            capacity *= 2;
            char* new_memory = (char*)realloc(*result, sizeof(char) * capacity);
        if (new_memory == NULL) return INVALID_MEMORY;
            *result = new_memory;
        }
    }

    for (int i = 0; i < *size / 2; i++){
        char temp = (*result)[i];
        (*result)[i] = (*result)[*size - i - 1];
        (*result)[*size - i - 1] = temp;
    }
    return OK;
}

enum errors st_table(long int x, long int*** result){
    if (x > 10) return INVALID_INPUT;
    *result = (long int**)malloc(11 * sizeof(long int*));
    if (*result == NULL) return INVALID_MEMORY;
    for (int i = 0; i < 11; i++){
        (*result)[i] = (long int*)malloc((x + 1) * sizeof(int*));
        if((*result)[i] == NULL)
        {
            for(int j = 0; j < i; ++j)
            {
                free((*result)[j]);
            }
            free(*result);
            return INVALID_MEMORY;
        }
    }
    for(int base = 0; base <= 10; ++base) {
        for (int degree = 0; degree <= x; ++degree) {
            (*result)[base][degree] = (long int) pow(base, degree);
        }
    }
    return OK;
}

enum errors nat_sum(long int x, long long int *result){
    int flag = 1;
    if (x <= 0){
        flag = -1;
        x = labs(x);
    }
    for (int i = 1; i <= x; i++){
        if ((*result + i) > INT_MAX || (*result + i) < INT_MIN) return INVALID_MEMORY;
        *result += i;
    }
    *result *= flag;
    return OK;
}

enum errors fact(long int x, unsigned long long int *result){
    *result = 1;
    if (x < 0) return INVALID_INPUT;
    for (int i = 2; i <= x; i++){
        if (*result*i > ULLONG_MAX || *result*i < INT_MIN) return INVALID_MEMORY;
        *result *= i;
    }
    return OK;
}

int main (int argc, char* argv[]) {
    if (argc != 3) return INVALID_INPUT;

    if (!((argv[1][0] == '/' || argv[1][0] == '-') && (argv[1][2] == '\0'))){
        printf("Ошибка ввода флага\n");
        return INVALID_INPUT;
    }

    long int number = 0;

    if(str_to_int(argv[2], &number) != OK)
    {
        printf("Ошибка: невалидное число\n");
        return INVALID_INPUT;
    }

    switch(argv[1][1]){
        case 'h':
            int* result1 = NULL;
            int size1 = 0;
            enum errors h = natural_to_100(number, &result1, &size1);
            if (h == INVALID_INPUT){
                printf("Ошибка. Деление на 0\n");
                return INVALID_INPUT;
            }
            if (h == INVALID_MEMORY){
                printf("Ошибка в памяти\n");
                if(result1 != NULL) free(result1);
                return INVALID_MEMORY;
            }
            if (size1 == 0) {
                printf("Таких чисел нет\n");
                break;
            }
            printf("Массив чисел:\n");
            for(int i = 0; i < size1; ++i)
            {
                printf("%d ", result1[i]);
            }
            printf("\n");
            if(result1 != NULL) free(result1);
            break;
        case 'p':
            if(is_prime(number)){
                printf("Число простое\n");
            }
            else{
                printf("Число составное\n");
            }
            break;
        case 's':
            char* result2 = NULL;
            int size2 = 0, flag = 0;
            enum errors s = divide_to_nums(number, &result2, &size2, &flag);
            if (s == INVALID_MEMORY){
                printf("Ошибка памяти\n");
                if(result2 != NULL) free(result2);
                return INVALID_MEMORY;
            }
            if (flag == 1){
                printf("- ");
            }
            for (int i = 0; i < size2; i++){
                printf("%c ", result2[i]);
            }
            printf("\n");
            if (result2 != NULL) free(result2);
            break;
        case 'e':
            long int** result3 = NULL;
            enum errors e = st_table(number, &result3);
            if (e == INVALID_INPUT || number < 0){
                printf("Ошибка ввода, число должно быть не больше 10\n");
                return INVALID_INPUT;
            }
            if (e == INVALID_MEMORY){
                printf("Ошибка памяти\n");
                //if (result3 != NULL) free(result3);
                return INVALID_MEMORY;
            }
            for (int i = 1; i < 11; i++){
                printf("Основание %d: ", i);
                for (int j = 0; j < number; j++){
                    printf("%ld ", result3[i][j]);
                }
                printf("\n");
            }
            for(int i = 0; i <= 10; i++){
                if(result3[i] != NULL) free(result3[i]);
            }
            if(result3 != NULL) free(result3);
            break;
        case 'a':
            long long int result4 = 0;
            enum errors a = nat_sum(number, &result4);
            if (a == INVALID_MEMORY){
                printf("Ошибка памяти\n");
                return INVALID_MEMORY;
            }
            printf("%lld \n", result4);
            break;
        case 'f':
            unsigned long long int result5 = 1;
            enum errors f = fact(number, &result5);
            if (f == INVALID_INPUT){
                printf("Ошибка ввода\n");
                return INVALID_INPUT;
            }
            if (f == INVALID_MEMORY){
                printf("Ошибка памяти\n");
                return INVALID_MEMORY;
            }
            printf("%llu\n", result5);
            break;

        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            break;
    }
    return 0;
}
