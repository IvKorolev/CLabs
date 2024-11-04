#include "operations.h"

enum errors create_str(char* input, String* result){
    if (input == NULL || result == NULL) {
        return INVALID_INPUT;
    }
    int size = strlen(input);
    result->array = malloc(sizeof(char) * (size + 1));
    if (result->array == NULL){
        return INVALID_MEMORY;
    }
    strcpy(result->array, input);
    result->length = size;
    return OK;
}

enum errors delete_str(String* input){
    if (input == NULL || input->array == NULL) {
        return INVALID_INPUT;
    }
    free(input->array);
    input->array = NULL;
    input->length = 0;
    return OK;
}

enum errors compare_srt(String* first, String* second, int *result){
    if (first == NULL || first->array == NULL || second == NULL || second->array == NULL) {
        return INVALID_INPUT;
    }
    int length_first = first->length;
    int length_second = second->length;
    if (length_first - length_second != 0){
        *result = length_first - length_second;
        return OK;
    }
    for (int i = 0; i < length_first; i++) {
        if (first->array[i] != second->array[i]) {
            *result = first->array[i] - second->array[i];
            return OK;
        }
    }
    *result = 0;
    return OK;
}

enum errors equivalence(String* first, String* second, int* flag){
    if (first == NULL || first->array == NULL || second == NULL || second->array == NULL) {
        return INVALID_INPUT;
    }
    if (first->length != second->length) {
        *flag = 0;
        return OK;
    }
    for (int i = 0; i < first->length; i++) {
        if (first->array[i] != second->array[i]) {
            *flag = 0;
            return OK;
        }
    }
    *flag = 1;
    return OK;
}

enum errors copy_to_existing(String* first, String* second){
    if (first == NULL || first->array == NULL || second == NULL || second->array == NULL) {
        return INVALID_INPUT;
    }
    int size = first->length;
    char* new_memory = malloc(sizeof(char) * size);
    if (new_memory == NULL){
        return INVALID_MEMORY;
    }

    for (int i = 0; i < size; i++) {
        new_memory[i] = first->array[i];
    }

    free(second->array);
    second->array = new_memory;
    second->length = size;

    return OK;
}

String* copy_to_new(String* first){
    if (first == NULL || first->array == NULL) {
        return NULL;
    }
    String* new_str = malloc(sizeof(String));
    if (new_str == NULL) {
        return NULL;
    }
    new_str->array = malloc(sizeof(char) * first->length);
    if (new_str->array == NULL) {
        free(new_str);
        return NULL;
    }
    for (int i = 0; i < first->length; i++) {
        new_str->array[i] = first->array[i];
    }
    new_str->length = first->length;
    return new_str;
}

enum errors concatenate(String* first, String* second){
    if (first == NULL || first->array == NULL || second == NULL || second->array == NULL) {
        return INVALID_INPUT;
    }
    int size = first->length + second->length;
    char* new_memory = malloc(sizeof(char) * (size + 1));
    if (new_memory == NULL){
        return INVALID_MEMORY;
    }

    memcpy(new_memory, first->array, first->length);
    memcpy(new_memory + first->length, second->array, second->length);
    new_memory[size] = '\0';

    free(first->array);
    first->array = new_memory;
    first->length = size;
    return OK;
}

enum errors create_post(char* town, char* street, int house_number, char* korpus, int apartment, char* index, post* post_office) {
    if (post_office == NULL) {
        return INVALID_INPUT;
    }

    post_office->this_building = malloc(sizeof(adress));
    if (post_office->this_building == NULL) {
        return INVALID_MEMORY;
    }

    enum errors status = create_adress(town, street, house_number, korpus, apartment, index, post_office->this_building);
    if (status != OK) {
        free(post_office->this_building);
        return status;
    }

    post_office->mass = malloc(sizeof(mail) * 0);
    if (post_office->mass == NULL) {
        delete_str(&post_office->this_building->town);
        delete_str(&post_office->this_building->street);
        delete_str(&post_office->this_building->korpus);
        delete_str(&post_office->this_building->index);
        free(post_office->this_building);
        return INVALID_MEMORY;
    }

    post_office->size = 0;

    return OK;
}

enum errors create_adress(char* town, char* street, int house_number, char* korpus, int apartment, char* index, adress* new_adress) {
    if (town == NULL || street == NULL || index == NULL || strlen(index) != 6 || house_number <= 0 || apartment <= 0){
        return INVALID_INPUT;
    }
    enum errors status;
    status = create_str(town, &new_adress->town);
    if (status != OK) return status;

    status = create_str(street, &new_adress->street);
    if (status != OK) return status;

    new_adress->house_number = house_number;

    status = create_str(korpus, &new_adress->korpus);
    if (status != OK) return status;

    new_adress->apartment = apartment;

    status = create_str(index, &new_adress->index);
    if (status != OK) return status;

    return OK;
}

enum errors create_mail(adress* adr, double weight, char* post_id, char* time_cr, char* time_d, mail* new_mail) {
    if (adr == NULL || post_id == NULL || strlen(post_id) != 14 || time_cr == NULL || time_d == NULL || weight < 0.0) {
        return INVALID_INPUT;
    }

    new_mail->adr = *adr;

    new_mail->weight = weight;

    enum errors status;
    status = create_str(post_id, &new_mail->post_id);
    if (status != OK) return status;

    status = create_str(time_cr, &new_mail->time_of_creation);
    if (status != OK) return status;

    status = create_str(time_d, &new_mail->time_of_delivery);
    if (status != OK) return status;

    return OK;
}

enum errors add_mail_to_post(post* post_office, mail new_mail){
    if (post_office == NULL) {
        return INVALID_INPUT;
    }
    int new_size = post_office->size + 1;

    mail* temp_mass = realloc(post_office->mass, new_size * sizeof(mail));
    if (temp_mass == NULL) {
        return INVALID_MEMORY;
    }
    post_office->mass = temp_mass;
    post_office->mass[post_office->size] = new_mail;
    post_office->size = new_size;

    return OK;
}

void print_all_mail(post* p) {
    if (p == NULL || p->mass == NULL) {
        printf("Нет доступных данных о посылках.\n");
        return;
    }

    if (p->size == 0) {
        printf("В почтовом отделении нет посылок.\n");
        return;
    }

    printf("Список всех посылок:\n");
    for (int i = 0; i < p->size; i++) {
        printf("Посылка %d:\n", i + 1);
        printf("  Почтовый ID: %s\n", p->mass[i].post_id.array);
        printf("  Время создания: %s\n", p->mass[i].time_of_creation.array);
        printf("  Время вручения: %s\n", p->mass[i].time_of_delivery.array);
        printf("  Адрес получателя:\n");
        printf("    Город: %s\n", p->mass[i].adr.town.array);
        printf("    Улица: %s\n", p->mass[i].adr.street.array);
        printf("    Номер дома: %d\n", p->mass[i].adr.house_number);
        printf("    Корпус: %s\n", p->mass[i].adr.korpus.array);
        printf("    Номер квартиры: %d\n", p->mass[i].adr.apartment);
        printf("    Индекс: %s\n", p->mass[i].adr.index.array);
        printf("  Вес: %.2f\n", p->mass[i].weight);
        printf("\n");
    }
}

enum errors delete_mail(mail* Mail){
    if (Mail == NULL){
        return INVALID_INPUT;
    }
    delete_str(&Mail->post_id);
    delete_str(&Mail->time_of_creation);
    delete_str(&Mail->time_of_delivery);
    return OK;
}

enum errors remove_mail(post* Post, const char* post_id){
    if (Post == NULL){
        return INVALID_INPUT;
    }
    for (int i = 0; i < Post->size; i++){
        if (strcmp(Post->mass[i].post_id.array, post_id) == 0){

            delete_mail(&Post->mass[i]);

            for (int j = i; j < Post->size - 1; j++){
                Post->mass[j] = Post->mass[j+1];
            }
            Post->size--;
            mail* new_memory = (mail*)realloc(Post->mass, Post->size * sizeof(mail));
            if (new_memory == NULL){
                return INVALID_MEMORY;
            }
            Post->mass = new_memory;
        }
    }
    return OK;
}

enum errors find_mail(post* Post, const char* post_id, mail* res){
    if (Post == NULL){
        return INVALID_INPUT;
    }
    for (int i = 0; i < Post->size; i++){
        if (strcmp(Post->mass[i].post_id.array, post_id) == 0){
            *res = Post->mass[i];
            return OK;
        }
    }
    return INVALID_INPUT;
}

enum errors print_mail(mail* Mail){
    if (Mail == NULL){
        return INVALID_INPUT;
    }
    printf("ID Посылки: %s\n", Mail->post_id.array);
    printf("Адрес получателя: %s, %s, %d, %s, %d, %s\n", Mail->adr.town.array,
           Mail->adr.street.array, Mail->adr.house_number, Mail->adr.korpus.array,
           Mail->adr.apartment, Mail->adr.index.array);
    printf("Данные посылки:\n");
    printf("Вес: %.2lf\n", Mail->weight);
    printf("Время создания %s\n", Mail->time_of_creation.array);
    printf("Время доставки %s\n", Mail->time_of_delivery.array);
    return OK;
}