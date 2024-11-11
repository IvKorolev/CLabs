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
    int cached_hash;
}hash_table_item;

typedef struct hash_table{
    hash_table_item** items;
    long int size;
}hash_table;

hash_table* create_table(int size);
int hash_function(char* key);
hash_table_item * create_item(char* key, char* value);
char* search_item(const hash_table* map, char* key);
void delete_hash_item(hash_table_item* item);
void delete_hash_table(hash_table* map);
void insert_item(hash_table* map, char* key, char* value, int hash);
void print_table(hash_table* map);
void calculate_chain_lengths(hash_table* map, int* min_len, int* max_len);
hash_table* resize_table(hash_table* old_map, int new_size);
void check_and_resize_table(hash_table** map);
enum errors process_file(FILE* input, FILE* output, hash_table* map);



#endif //CLABS_OPERATIONS_H
