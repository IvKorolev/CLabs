#include "operations.h"

const char* get_filename(const char* path) {
    const char* last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        return last_slash + 1;
    }
    return path;
}

enum errors create_list(FILE* input, Employee** result, int *size){
    int capacity = 1;
    *result = (Employee*)malloc(sizeof(Employee) * capacity);
    if (*result == NULL){
        return INVALID_MEMORY;
    }
    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), input) != NULL){
        Employee person;
        char id_str[50], payment_str[50];
        if (sscanf(buffer, "%s %s %s %s", id_str, person.name, person.last_name, payment_str) == 4){
            char *endptr;
            person.id = strtol(id_str, &endptr, 10);
            if (*endptr != '\0' || person.id < 0) {
                continue;
            }
            person.payment = strtod(payment_str, &endptr);
            if (*endptr != '\0' || person.payment < 0) {
                continue;
            }
            (*result)[(*size)++] = person;
            if (*size == capacity){
                capacity *= 2;
                Employee *new_memory = realloc(*result, capacity * sizeof(Employee));
                if (new_memory == NULL){
                    free(*result);
                    return INVALID_MEMORY;
                }
                *result = new_memory;
            }
        }
        else{
            continue;
        }
    }
    return OK;
}