#include "operations.h"

hash_table* create_table(int size){
    hash_table* map = (hash_table*)malloc(sizeof(hash_table));
    if (map == NULL){
        return NULL;
    }
    map->size = size;
    map->items = (hash_table_item**)malloc(sizeof(hash_table_item) * size);
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

    item->znachenie = (values*)malloc(sizeof(values));
    if(item->znachenie == NULL){
        free(item->key);
        free(item);
        return NULL;
    }

    item->znachenie->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    if (item->znachenie->value == NULL){
        free(item->key);
        free(item->znachenie);
        free(item);
        return NULL;
    }
    strcpy(item->znachenie->value, value);
    item->znachenie->next = NULL;

    return item;
}

char* search_item(const hash_table* map, char* key){
    int index = hash_function(key) % map->size;
    hash_table_item* item = map->items[index];
    if (item != NULL){
        if (strcmp(item->key, key) == 0){
            return item->znachenie->value;
        }
    }
    return NULL;
}

void delete_hash_item(hash_table_item* item){
    values* current = item->znachenie;
    while (current != NULL) {
        values* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(item->key);
    free(item);
}

void delete_hash_table(hash_table* map){
    for(int i = 0; i < map->size; i++){
        if (map->items[i] != NULL){
            delete_hash_item(map->items[i]);
        }
    }
    free(map->items);
    free(map);
}

void insert_item(hash_table* map, char* key, char* value, int hash){
    if (map == NULL || key == NULL || value == NULL) {
        return;
    }

    int index = hash % map->size;
    hash_table_item* item = map->items[index];

    if (item == NULL) {
        map->items[index] = create_item(key, value);
        return;
    }

    hash_table_item* current = item;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            values* val_current = current->znachenie;
            while (val_current->next != NULL) {
                if (strcmp(val_current->value, value) == 0) {
                    return;
                }
                val_current = val_current->next;
            }

            if (strcmp(val_current->value, value) != 0) {
                val_current->next = (values*)malloc(sizeof(values));
                val_current->next->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
                strcpy(val_current->next->value, value);
                val_current->next->next = NULL;
            }
            return;
        }
        current = NULL;
    }

    hash_table_item* new_item = create_item(key, value);
    if (new_item == NULL) {
        return;
    }

    if (map->items[index] != NULL) {
        delete_hash_item(new_item);
    }
    else {
        map->items[index] = new_item;
    }
}

void print_table(hash_table* map){
    printf("Hash table:\n");
    for (int i = 0; i < map->size; i++){
        if (map->items[i] != NULL){
            printf("Values for key %s: ", map->items[i]->key);
            values* current = map->items[i]->znachenie;
            while (current != NULL) {
                printf("%s ", current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

void calculate_chain_lengths(hash_table* map, int* min_len, int* max_len){
    *min_len = map->size;
    *max_len = 0;

    for (int i = 0; i < map->size; i++){
        int chain_len = 0;
        hash_table_item* item = map->items[i];

        while (item->znachenie != NULL){
            chain_len++;
            item->znachenie = item->znachenie->next;
        }

        if (chain_len > 0 && chain_len < *min_len){
            *min_len = chain_len;
        }
        if (chain_len > *max_len){
            *max_len = chain_len;
        }
    }
}

hash_table* resize_table(hash_table* old_map, int new_size){
    hash_table* new_map = create_table(new_size);
    if (new_map == NULL){
        return NULL;
    }

    for (int i = 0; i < old_map->size; i++){
        hash_table_item* item = old_map->items[i];

        while (item != NULL){
            values* current_value = item->znachenie;
            while (current_value != NULL){
                insert_item(new_map, item->key, current_value->value, item->cached_hash);
                current_value = current_value->next;
            }
            item = NULL;
        }
    }

    delete_hash_table(old_map);
    return new_map;
}

void check_and_resize_table(hash_table** map){
    int min_len, max_len;
    calculate_chain_lengths(*map, &min_len, &max_len);

    if (max_len >= 2 * min_len){
        int new_size = (*map)->size * 2;
        *map = resize_table(*map, new_size);
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
    fprintf(output ,"\n");

    while (fscanf(input, "%1023s", buffer) == 1) {
        char* mapped_value = search_item(map, buffer);
        if (mapped_value) {
            fprintf(output, "%s ", mapped_value);
        } else {
            fprintf(output, "%s ", buffer);
        }
    }
    return OK;
}