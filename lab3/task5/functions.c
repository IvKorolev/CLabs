#include "operations.h"

const char* get_filename(const char* path) {
    const char* last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        return last_slash + 1;
    }
    return path;
}

enum errors create_list(FILE* input, Student ** result, int* size){
    int capacity = 1;
    *result = (Student*)malloc(sizeof(Student) * capacity);
    if(*result == NULL){
        return INVALID_MEMORY;
    }
    char buffer[1024];
    *size = 0;
    while(fgets(buffer, 1023, input) != NULL){
        Student person;
        char temp_grades[6];
        if(sscanf(buffer, "%d:%49[^:]:%49[^:]:%14[^:]:%5s", &person.id, person.surname, person.name, person.group, temp_grades) == 5){
            if (strlen(temp_grades) != 5){
                continue;
            }
            person.grades = (unsigned char*)malloc(6 * sizeof(unsigned char)); // 5 оценок + завершающий ноль
            if (person.grades == NULL) {
                free(*result);
                return INVALID_MEMORY;
            }
            strcpy((char*)person.grades, temp_grades);
        }
        else{
            continue;
        }
        (*result)[(*size)++] = person;
        if (*size == capacity){
            capacity *= 2;
            Student *new_memory = realloc(*result, capacity * sizeof(Student));
            if (new_memory == NULL){
                for (int i = 0; i < *size; i++) {
                    free((*result)[i].grades);
                }
                free(*result);
                return INVALID_MEMORY;
            }
            *result = new_memory;
        }
    }
    return OK;
}

void free_student_list(Student* list, int size) {
    for (int i = 0; i < size; i++) {
        free(list[i].grades);
    }
    free(list);
}

enum errors search(Student* list, const char* output_filename, char* pod, char flag, int size){
    FILE* output = fopen(output_filename, "w");  // Открываем файл в режиме "w" для перезаписи
    if (output == NULL) {
        printf("Ошибка открытия выходного файла\n");
        return INVALID_INPUT;
    }
    int found = 0;
    if (flag == 'a'){
        int ide = strtol(pod, NULL, 10);
        for (int i = 0; i < size; i++){
            if (list[i].id == ide){
                double sum = 0;
                for (int j = 0; j < 5; j++) {
                    sum += list[i].grades[j] - '0';
                }
                double average = sum / 5;
                fprintf(output, "%d:%s:%s:%s:%.2f\n", list[i].id, list[i].surname, list[i].name, list[i].group, average);
                found = 1;
            }
        }
    }
    else if (flag == 'b'){
        for (int i = 0; i < size; i++){
            if (strcmp(list[i].surname, pod) == 0){
                double sum = 0;
                for (int j = 0; j < 5; j++) {
                    sum += list[i].grades[j] - '0';
                }
                double average = sum / 5;
                fprintf(output, "%d:%s:%s:%s:%.2f\n", list[i].id, list[i].surname, list[i].name, list[i].group, average);
                found = 1;
            }
        }
    }
    else if (flag == 'c'){
        for (int i = 0; i < size; i++){
            if (strcmp(list[i].name, pod) == 0){
                double sum = 0;
                for (int j = 0; j < 5; j++) {
                    sum += list[i].grades[j] - '0';
                }
                double average = sum / 5;
                fprintf(output, "%d:%s:%s:%s:%.2f\n", list[i].id, list[i].surname, list[i].name, list[i].group, average);
                found = 1;
            }
        }
    }
    else if (flag == 'd'){
        for (int i = 0; i < size; i++){
            if (strcmp(list[i].group, pod) == 0){
                double sum = 0;
                for (int j = 0; j < 5; j++) {
                    sum += list[i].grades[j] - '0';
                }
                double average = sum / 5;
                fprintf(output, "%d:%s:%s:%s:%.2f\n", list[i].id, list[i].surname, list[i].name, list[i].group, average);
                found = 1;
            }
        }
    }
    fclose(output);
    if (found == 0){
        return INVALID_INPUT;
    }
    else return OK;
}



enum errors sort(Student* list, const char* output_filename, char* pod, char flag, int size){
    FILE* output = fopen(output_filename, "w");  // Открываем файл в режиме "w" для перезаписи
    if (output == NULL) {
        printf("Ошибка открытия выходного файла\n");
        return INVALID_INPUT;
    }
    return OK;
}
