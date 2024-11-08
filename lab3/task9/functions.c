#include "operations.h"

Node* create(char* word){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL){
        return NULL;
    }
    int size = strlen(word);
    new_node->word = (char*)malloc(sizeof(char) * (size + 1));
    if (new_node->word== NULL){
        free(new_node);
        return NULL;
    }
    strcpy(new_node->word, word);
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* insert(Node* root, char* word){
    if (root == NULL){
        return create(word);
    }
    int cmp = strcmp(word, root->word);
    if (cmp == 0){
        root->count++;
    }
    else if(cmp > 0){
        root->right = insert(root->right, word);
    }
    else{
        root->left = insert(root->left, word);
    }
    return root;
}

Node* search(Node* root, char* word){
    if (root == NULL){
        return NULL;
    }
    int cmp = strcmp(word, root->word);
    if(cmp == 0){
        return root;
    }
    else if(cmp < 0){
        return search(root->left, word);
    }
    else{
        return search(root->right, word);
    }
}

