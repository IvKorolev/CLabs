#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#define HASHSIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

typedef struct values{
    char* value;
    struct values* next;
}values;

typedef struct hash_table_item{
    char* key;
    values* znachenie;
}hash_table_item;

typedef struct hash_table{
    hash_table_item** items;
    long int size;
}hash_table;

hash_table* create_table(int size);
int hash_function(char* key);
hash_table_item * create_item(char* key, char* value);
void insert_item(hash_table* map, char* key, char* value);
char* search_item(const hash_table* map, char* key);




#endif //CLABS_OPERATIONS_H
