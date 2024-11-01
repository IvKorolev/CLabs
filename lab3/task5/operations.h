#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

typedef struct Student{
    int id;
    char surname[50];
    char name[50];
    char group[15];
    unsigned char* grades;
}Student;

const char* get_filename(const char* path);
enum errors create_list(FILE* input, Student ** result, int* size);
void free_student_list(Student* list, int size);
enum errors search(Student* list, const char* output_filename, char* pod, char flag, int size);

#endif //CLABS_OPERATIONS_H
