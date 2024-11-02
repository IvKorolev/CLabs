#include "operations.h"

const char* get_filename(const char* path) {
    const char* last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        return last_slash + 1;
    }
    return path;
}

//const char* get_filename(const char* path){
//    const char result[PATH_MAX];
//    if (GetFullPathName(path, PATH_MAX, result, NULL) == 0){
//        return path;
//    }
//    return result;
//}

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
    FILE* output = fopen(output_filename, "a");
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
    fprintf(output, "\n");
    fclose(output);
    if (found == 0){
        return INVALID_INPUT;
    }
    else return OK;
}

int compare_by_id(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return studentA->id - studentB->id;
}

int compare_by_surname(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return strcmp(studentA->surname, studentB->surname);
}

int compare_by_name(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return strcmp(studentA->name, studentB->name);
}

int compare_by_group(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return strcmp(studentA->group, studentB->group);
}

enum errors sort(Student* list, const char* output_filename, char* pod, char flag, int size) {
    FILE *output = fopen(output_filename, "a");
    if (output == NULL) {
        printf("Ошибка открытия выходного файла\n");
        return INVALID_INPUT;
    }

    if (flag == 'a'){
        qsort(list, size, sizeof(Student), compare_by_id);
    }
    else if (flag == 'b'){
        qsort(list, size, sizeof(Student), compare_by_surname);
    }
    else if (flag == 'c'){
        qsort(list, size, sizeof(Student), compare_by_name);
    }
    else if (flag == 'd'){
        qsort(list, size, sizeof(Student), compare_by_group);
    }
    else{
        fclose(output);
        return INVALID_INPUT;
    }
    for (int i = 0; i < size; i++) {
        fprintf(output, "%d:%s:%s:%s:%s\n", list[i].id, list[i].surname, list[i].name, list[i].group, list[i].grades);
    }
    fprintf(output, "\n");
    fclose(output);
    return OK;
}

float calculate_average(unsigned char* grades){
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += grades[i] - '0';
    }
    return (float)sum / 5;
}

float calculate_overall_average(Student* list, int size){
    float total_average = 0;
    for (int i = 0; i < size; i++) {
        total_average += calculate_average(list[i].grades);
    }
    return total_average / size;
}

enum errors output_above_average_students(Student* list, int size, const char* output_filename){
    FILE *output = fopen(output_filename, "a");
    if (output == NULL) {
        printf("Ошибка открытия выходного файла\n");
        return INVALID_INPUT;
    }
    float overall_average = calculate_overall_average(list, size);
    fprintf(output, "Студенты с средним баллом выше %.2f:\n", overall_average);

    for (int i = 0; i < size; i++) {
        float student_average = calculate_average(list[i].grades);
        if (student_average > overall_average) {
            fprintf(output, "%d:%s:%s:%s:%.2f\n", list[i].id, list[i].surname, list[i].name, list[i].group, student_average);
        }
    }
    fprintf(output, "\n");
    fclose(output);
    return OK;
}