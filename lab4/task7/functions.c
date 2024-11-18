#include "operations.h"

enum errors str_to_int(const char* x, long int* res){
    char symbol;
    if (sscanf(x, "%ld%c", res, &symbol) != 1){
        return INVALID_INPUT;
    }

    if (*res >= INT_MAX || *res <= INT_MIN){
        return INVALID_INPUT;
    }

    return OK;
}

int compare(const void* a, const void* b){
    MemoryCell* mc1 = (MemoryCell*)a;
    MemoryCell* mc2 = (MemoryCell*)b;
    return strcmp(mc1->name, mc2->name);
}

enum errors check_if_print(const char* buffer, MemoryCell* res, int size){
    if (strncmp(buffer, "print", 5) == 0 && strlen(buffer) == 6){
        for (int i = 0; i < size; i++){
            printf("%s: %d\n", res[i].name, res[i].value);
        }
        printf("\n");
        return OK;
    }
    else if (strncmp(buffer, "print", 5) == 0){
        char output[100];
        sscanf(buffer + 6, "%99s", output);
        output[strlen(output) - 1] = '\0';
        for (int i = 0; i < size; i++){
            if (strcmp(output, res[i].name) == 0){
                printf("%d\n", res[i].value);
            }
        }
        return OK;
    }
    else{
        return INVALID_INPUT;
    }
}

enum errors search_value(MemoryCell* res, char* argument, int size, long int* resultation){
    int left = 0;
    int right = size - 1;
    while (left <= right){
        int mid = left + (right - left) / 2;
        int result = strcmp(argument, res[mid].name);
        if (result == 0){
            *resultation = res[mid].value;
            return OK;
        }
        if (result < 0){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return NOT_DECLARED;
}

enum errors search_value_to_new(MemoryCell* res, char* argument, int size, long int* resultation){
    int left = 0;
    int right = size - 1;
    while (left <= right){
        int mid = left + (right - left) / 2;
        int result = strcmp(argument, res[mid].name);
        if (result == 0){
            res[mid].value = *resultation;
            return OK;
        }
        if (result < 0){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return NOT_FOUND;
}

enum errors add_Cell(MemoryCell** res, char* first_argument, long int num, int* size, int* capacity) {
    if (search_value_to_new(*res, first_argument, *size, &num) == OK){
        free(first_argument);
        return OK;
    }

    if (*size == *capacity) {
        *capacity *= 2;
        MemoryCell* new_memory = realloc(*res, sizeof(MemoryCell) * (*capacity));
        if (new_memory == NULL) {
            free(first_argument);
            return INVALID_MEMORY;
        }
        *res = new_memory;
    }

    (*res)[*size].name = first_argument;
    (*res)[*size].value = num;
    (*size)++;
    qsort(*res, *size, sizeof(MemoryCell), compare);
    return OK;
}

enum errors process_line(char* buffer, MemoryCell* res, int* size, int* capacity){
    char operation;
    char* first_argument = NULL;
    char* after_eq = NULL;
    char* second_argument = NULL;
    char* third_argument = NULL;
    int flag = 0;

    buffer[strlen(buffer) - 1] = '\0';

    for (int i = 0; i < strlen(buffer) - 1; i++){
        if (buffer[i] == '='){
            first_argument = malloc(sizeof(char) * (i + 1));
            if (first_argument == NULL){
                return INVALID_MEMORY;
            }
            strncpy(first_argument, buffer, i);
            first_argument[i] = '\0';
            after_eq = strdup(buffer + i + 1);
            if (after_eq == NULL){
                free(first_argument);
                return INVALID_MEMORY;
            }
            after_eq[strlen(after_eq) - 2] = '\0';
            break;
        }
    }

    for (int i = 0; i < strlen(after_eq); i++){
        if (!isdigit(after_eq[i]) && !isalpha(after_eq[i])){
            operation = after_eq[i];
            flag = 1;
            third_argument = strdup(after_eq + i + 1);
            second_argument = malloc(sizeof(char) * (i + 1));
            if (second_argument == NULL){
                free(first_argument);
                free(after_eq);
                return INVALID_MEMORY;
            }
            strncpy(second_argument, after_eq, i);
            second_argument[i] = '\0';
            break;
        }
    }

    if (flag == 0){
        second_argument = after_eq;
        if ((second_argument[0] == '-' && isdigit(second_argument[1])) || isdigit(second_argument[0])){
            long int num;
            enum errors chislo = str_to_int(second_argument, &num);
            if (chislo != OK){
                free(first_argument);
                free(second_argument);
                return INVALID_INPUT;
            }
            enum errors status_add = add_Cell(&res, first_argument, num, size, capacity);
            if (status_add != OK) return INVALID_MEMORY;
        }
        else{
            long int found;
            enum errors status_found = search_value(res, second_argument, *size, &found);
            if (status_found != OK){
                free(first_argument);
                free(second_argument);
                free(after_eq);
                return NOT_DECLARED;
            }
            enum errors status_add = add_Cell(&res, first_argument, found, size, capacity);
            if (status_add != OK) return INVALID_MEMORY;
        }
    }
    else{
        long int first_to_op, second_to_op;
        enum errors status;

        if (isdigit(second_argument[0]) || (second_argument[0] == '-' && isdigit(second_argument[1]))){
            status = str_to_int(second_argument, &first_to_op);
        }
        else{
            status = search_value(res, second_argument, *size, &first_to_op);
        }
        if (status != OK) {
            free(first_argument);
            free(second_argument);
            free(third_argument);
            free(after_eq);
            return status;
        }

        if (isdigit(third_argument[0]) || (third_argument[0] == '-' && isdigit(third_argument[1]))){
            status = str_to_int(third_argument, &second_to_op);
        }
        else{
            status = search_value(res, third_argument, *size, &second_to_op);
        }
        if (status != OK) {
            free(first_argument);
            free(second_argument);
            free(third_argument);
            free(after_eq);
            return status;
        }

        int resultat = 0;
        switch (operation){
            case '+':
                resultat = first_to_op + second_to_op;
                break;
            case '-':
                resultat = first_to_op - second_to_op;
                break;
            case '*':
                resultat = first_to_op * second_to_op;
                break;
            case '/':
                resultat = second_to_op ? first_to_op / second_to_op : 0;
                break;
            case '%':
                resultat = second_to_op ? first_to_op % second_to_op : 0;
                break;
        }
        enum errors status_add = add_Cell(&res, first_argument, resultat, size, capacity);
        if (status_add != OK) return INVALID_MEMORY;
    }

    if (flag == 1){
        free(second_argument);
        free(third_argument);
    }
    free(after_eq);
    return OK;
}

enum errors process_file(FILE* input, MemoryCell** res) {
    int capacity = 100;
    int size = 0;
    *res = malloc(sizeof(MemoryCell) * capacity);
    if (*res == NULL) {
        return INVALID_MEMORY;
    }

    char buffer[1024];
    while (fgets(buffer, 1023, input) != NULL) {
        if (check_if_print(buffer, *res, size) == OK) continue;

        enum errors status_line = process_line(buffer, *res, &size, &capacity);
        if (status_line != OK) {
            for (int i = 0; i < size; i++) {
                free((*res)[i].name);
            }
            free(*res);
            return status_line;
        }
    }

    for (int i = 0; i < size; i++) {
        free((*res)[i].name);
    }
    free(*res);
    return OK;
}