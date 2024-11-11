#include "operations.h"

hash_table* create_table(int size){
    hash_table* map = (hash_table*)malloc(sizeof(hash_table));
    if (map == NULL){
        return NULL;
    }
    map->size = size;
    map->items = (hash_table_item*)malloc(sizeof(hash_table_item) * size);
    if (map->items == NULL){
        free(map);
        return NULL;
    }
    return map;
}

int hash_function(char* key){
    int num = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
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

    item->key = (char*)malloc(sizeof(char*) * (strlen(key) + 1));
    if(item->key == NULL)
    {
        free(item);
        return NULL;
    }
    strcpy(item->key, key);

    item->znachenie = (values*)malloc(sizeof(values));
    if(item->znachenie == NULL){
        free(item->key);
        free(item);
        return NULL;
    }

    item->znachenie->value = (char*)malloc(sizeof(char*) * (strlen(value) + 1));
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
void insert_item(hash_table* map, char* key, char* value){
    if(map == NULL || key == NULL || value == NULL){
        return;
    }
    int hash = hash_function(key);
    hash_table_item* item = create_item(key, value);
    int index = hash % map->size;
    if (map->items[index] == NULL){
        map->items[index] = item;
    }
    else{
        hash_table_item* current = map->items[index];
        while(current->znachenie->next != NULL){
            if (strcmp(current->key, item->key) == 0){
                return;
            }
            current = current->znachenie->next;
        }
        if (strcmp(current->key, item->key) == 0){
            return;
        }
        current->znachenie->next = item->znachenie;
    }
}

char* search_item(const hash_table* map, char* key){
    int index = hash_function(key) % map->size;
    hash_table_item* item = map->items[index];
    if (item != NULL){
        if (strcmp(item->key, key) == 0){
            return item->value;
        }
    }
    return NULL;
}

