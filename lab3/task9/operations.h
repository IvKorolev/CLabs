#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
};

typedef struct Node{
    char* word;
    int count;
    struct Node* left;
    struct Node* right;
}Node;

Node* create(char* word);
Node* insert(Node* root, char* word);
Node* search(Node* root, char* word);


#endif //CLABS_OPERATIONS_H
