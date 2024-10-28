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
        sscanf(buffer, "%d %s %s %lf", &person.id, person.name, person.last_name, &person.payment);
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
    return OK;
}