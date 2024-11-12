#include "operations.h"

hash_table* create_table(int size){
    hash_table* map = (hash_table*)malloc(sizeof(hash_table));
    if (map == NULL){
        return NULL;
    }
    map->size = size;
    map->items = (hash_table_item**)malloc(sizeof(hash_table_item*) * size);
    if (map->items == NULL){
        free(map);
        return NULL;
    }
    return map;
}

int hash_function(char* key){
    int num = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++){
        if (key[i] >= '0' && key[i] <= '9')
            num = num*62 + key[i] - '0';
        else if (key[i] >= 'A' && key[i] <= 'Z')
            num = num*62 + key[i] - 'A' + 10;
        else if (key[i] >= 'a' && key[i] <= 'z')
            num = num*62 + key[i] - 'a' + 36;
    }
    return num;
}

hash_table_item * create_item(char* key, char* value){
    hash_table_item* item = (hash_table_item*)malloc(sizeof(hash_table_item));
    if (value == NULL || item == NULL){
        return NULL;
    }

    item->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
    if(item->key == NULL)
    {
        free(item);
        return NULL;
    }
    strcpy(item->key, key);
    item->cached_hash = hash_function(key);

    item->znachenie = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    if (item->znachenie == NULL){
        free(item->key);
        free(item);
        return NULL;
    }
    strcpy(item->znachenie, value);
    item->next = NULL;

    return item;
}

char* search_item(const hash_table* map, char* key){
    int index = hash_function(key) % map->size;
    hash_table_item* item = map->items[index];
    while (item != NULL){
        if (strcmp(item->key, key) == 0){
            return item->znachenie;
        }
        item = item->next;
    }
    return NULL;
}

void delete_hash_item(hash_table_item* item){
    free(item->znachenie);
    free(item->key);
    free(item);
}

void delete_hash_table(hash_table* map){
    for(int i = 0; i < map->size; i++){
        hash_table_item* item = map->items[i];
        while (item != NULL){
            hash_table_item* next_item = item->next;
            delete_hash_item(item);
            item = next_item;
        }
    }
    free(map->items);
    free(map);
}

void insert_item(hash_table* map, char* key, char* value, int hash) {
    if (map == NULL || key == NULL || value == NULL) {
        return;
    }

    int index = hash % map->size;
    hash_table_item* item = create_item(key, value);
    if (item == NULL) {
        return;
    }

    if(map->items[index] == NULL){
        map->items[index] = item;
    }
    else{
        hash_table_item* current = map->items[index];
        while(current->next != NULL){
            if(strcmp(current->key, item->key) == 0)
            {
                delete_hash_item(item);
                return;
            }
            current = current->next;
        }
        if(strcmp(current->key, item->key) == 0)
        {
            delete_hash_item(item);
            return;
        }
        current->next = item;
    }
}

void print_table(hash_table* map){
    printf("Hash table:\n");
    for (int i = 0; i < map->size; i++){
        if (map->items[i] != NULL){
            printf("Values for key %s: ", map->items[i]->key);
            hash_table_item* current = map->items[i];
            while (current != NULL) {
                printf("%s ", current->znachenie);
                current = current->next;
            }
            printf("\n");
        }
    }
}

void calculate_chain_lengths(hash_table* map, int* min_len, int* max_len) {
    *min_len = map->size;
    *max_len = 0;

    for (int i = 0; i < map->size; i++) {
        int chain_len = 0;
        hash_table_item* item = map->items[i];

        while (item != NULL) {
            chain_len++;
            printf("Current chain length at index %d: %d\n", i, chain_len);  // Отладка
            item = item->next;
        }

        if (chain_len > 0 && chain_len < *min_len) {
            *min_len = chain_len;
        }
        if (chain_len > *max_len) {
            *max_len = chain_len;
        }
    }
}

void* resize_table(hash_table* old_map, int new_size) {
    hash_table_item** old = old_map->items;
    int old_size = old_map->size;
    old_map->size = new_size;
    old_map->items = (hash_table_item**)calloc(new_size, sizeof(hash_table_item*));

    for (int i = 0; i < old_size; i++) {
        hash_table_item* item = old[i];

        while (item != NULL) {
            printf("Resizing item with key: %s\n", item->key);
            printf(" - Copying value: %s\n", item->znachenie);
            insert_item(old_map, item->key, item->znachenie, item->cached_hash);
            hash_table_item* old_item = item;
            item = item->next;
            delete_hash_item(old_item);
        }
    }

    free(old);
    return NULL;
}

void check_and_resize_table(hash_table** map){
    int min_len, max_len;
    calculate_chain_lengths(*map, &min_len, &max_len);

    if (max_len >= 2 * min_len){
        int new_size = (*map)->size * 2;
        resize_table(*map, new_size);
        printf("Hash table resized to %d\n", new_size);
    }
}

enum errors process_file(FILE* input, FILE* output, hash_table* map){
    char buffer[1024];
    char key[75];
    char value[75];

    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        if (strncmp(buffer, "#define ", 8) == 0) {
            if (sscanf(buffer + 8, "%74s %74s", key, value) == 2) {
                fprintf(output, "%s", buffer);
                insert_item(map, key, value, hash_function(key));
            }
        } else {
            fseek(input, -strlen(buffer), SEEK_CUR);
            break;
        }
    }
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        char* token = strtok(buffer, " \n");
        int first_word = 1;

        while (token != NULL) {
            char* mapped_value = search_item(map, token);
            if (first_word) {
                fprintf(output, "%s", mapped_value ? mapped_value : token);
                first_word = 0;
            }
            else{
                fprintf(output, " %s", mapped_value ? mapped_value : token);
            }
            token = strtok(NULL, " \n");
        }
        fprintf(output, "\n");
    }
    return OK;
}