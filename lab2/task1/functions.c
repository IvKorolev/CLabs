#include "operations.h"

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

int string_length(const char* str){
    int length = 0;
    while(*str != '\0'){
        length++;
        str++;
    }
    return length;
}

enum errors reverse_str(const char* str, char** result){
    int length = string_length(str);
    (*result) = (char*)malloc(sizeof(char) * (length + 1));
    if (*result == NULL){
        free(result);
        return INVALID_MEMORY;
    }
    int i = 0;
    --length;
    while(length >= 0)
    {
        (*result)[i++] = str[length--];
    }
    (*result)[i] = '\0';
    return OK;
}

enum errors high_register(const char* str, char** result){
    int length = string_length(str);
    (*result) = (char*)malloc(sizeof(char) * (length + 1));
    if (*result == NULL){
        free(result);
        return INVALID_MEMORY;
    }
    for(int i = 0; i < length; i++){
        if (i % 2 != 0 && str[i] >= 'a' && str[i] <= 'z'){
            (*result)[i] = str[i] - 32;
        }
        else{
            (*result)[i] = str[i];
        }
    }
    (*result)[length] = '\0';
    return OK;
}

enum errors new_str(const char* str, char** result){
    int length = string_length(str);
    (*result) = (char*)malloc(sizeof(char) * (length + 1));
    if (*result == NULL){
        free(result);
        return INVALID_MEMORY;
    }
    int index = 0;
    for(int i = 0; i < length; ++i)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            (*result)[index++] = str[i];
        }
    }
    for(int i = 0; i < length; ++i)
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            (*result)[index++] = str[i];
        }
    }
    for(int i = 0; i < length; ++i)
    {
        if( !(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] >= 'a' && str[i] <= 'z') &&
            !(str[i] >= 'A' && str[i] <= 'Z'))
        {
            (*result)[index++] = str[i];
        }
    }
    (*result)[index] = '\0';
    return OK;
}

void concat_string(char* str, char** result, int* len){
    for(int i = 0; str[i] != '\0'; ++i)
    {
        (*result)[(*len)++] = str[i];
    }
    (*result)[(*len)] = '\0';
}

enum errors concatenate_all(char** strs, int count_str, char** result, unsigned int res){
    int len = 0, capacity = 0;
    for(int i = 0; i < count_str; ++i)
    {
        len = string_length(strs[i]);
        if (len > capacity) capacity = len;
    }
    capacity *= count_str;
    len = 0;
    (*result) = (char *)malloc(sizeof(char) * (capacity + 1));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    srand(res);
    int rand_num;
    for(int i = 0; i < count_str; ++i)
    {
        rand_num = rand() % count_str;
        concat_string(strs[rand_num], result, &len);
    }
    return OK;
}