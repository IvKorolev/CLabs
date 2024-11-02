#include "operations.h"

int main(int argc, char* argv[]){
    String str1, str2, copy_str, concat_str;
    int result;
    int flag;

    printf("Testing create_str:\n");
    if (create_str("Hello", &str1) == OK) {
        printf("str1: %s, length: %d\n", str1.array, str1.length);
    } else {
        printf("Failed to create str1\n");
    }

    if (create_str("World", &str2) == OK) {
        printf("str2: %s, length: %d\n", str2.array, str2.length);
    } else {
        printf("Failed to create str2\n");
    }

    printf("\nTesting compare_srt:\n");
    if (compare_srt(&str1, &str2, &result) == OK) {
        if (result == 0) {
            printf("str1 and str2 are equal.\n");
        } else if (result > 0) {
            printf("str1 is greater than str2.\n");
        } else {
            printf("str1 is less than str2.\n");
        }
    } else {
        printf("Failed to compare str1 and str2\n");
    }

    printf("\nTesting equivalence:\n");
    if (equivalence(&str1, &str2, &flag) == OK) {
        if (flag) {
            printf("str1 and str2 are equivalent.\n");
        } else {
            printf("str1 and str2 are not equivalent.\n");
        }
    } else {
        printf("Failed to check equivalence\n");
    }

    printf("\nTesting copy_to_existing:\n");
    if (create_str("", &copy_str) == OK && copy_to_existing(&str1, &copy_str) == OK) {
        printf("copy_str (copied from str1): %s, length: %d\n", copy_str.array, copy_str.length);
    } else {
        printf("Failed to copy str1 to copy_str\n");
    }

    printf("\nTesting copy_to_new:\n");
    String* new_str = copy_to_new(&str2);
    if (new_str != NULL) {
        printf("new_str (copied from str2): %s, length: %d\n", new_str->array, new_str->length);
        delete_str(new_str);
        free(new_str);
    } else {
        printf("Failed to create a new copy of str2\n");
    }

    printf("\nTesting concatenate:\n");
    if (concatenate(&str1, &str2) == OK) {
        printf("Concatenated str1 + str2: %s, length: %d\n", str1.array, str1.length);
    } else {
        printf("Failed to concatenate str1 and str2\n");
    }

    printf("\nTesting delete_str:\n");
    if (delete_str(&str1) == OK) {
        printf("str1 successfully deleted.\n");
    } else {
        printf("Failed to delete str1\n");
    }

    if (delete_str(&str2) == OK) {
        printf("str2 successfully deleted.\n");
    } else {
        printf("Failed to delete str2\n");
    }

    if (delete_str(&copy_str) == OK) {
        printf("copy_str successfully deleted.\n");
    } else {
        printf("Failed to delete copy_str\n");
    }

    post my_post_office;
    char town[100], street[100], korpus[100], index[100];
    int house_number, apartment;
    double weight;
    char post_id[15], time_cr[20], time_d[20];

    printf("\n\n\nСоздайте почтовое отделение: введите его адрес (город, ул, дом, корпус, номер кв, индекс)\n");

    scanf("%s %s %d %s %d %s", town, street, &house_number, korpus, &apartment, index);

    if (create_post(town, street, house_number, korpus, apartment, index, &my_post_office) != OK) {
        printf("Ошибка при создании почтового отделения.\n");
        return 1;
    }
    printf("Теперь вводите данные почтовых отправлений (введите 'Stop' для завершения):\n");
    printf("Сначала нужно ввести адрес, куда поедет посылка (город, ул, дом, корпус, номер кв, индекс)\n");
    printf("В таком формате: вес, идентиф = 14 символов, время созд и вручения: (dd:MM:yyyy hh:mm:ss)\n");
    printf("Вводите данные через пробел\n");
    while(1){
        adress new_adress;
        scanf("%s %s %d %s %d %s", town, street, &house_number, korpus, &apartment, index);
        if (create_adress(town, street, house_number, korpus, apartment, index, &new_adress) != OK){
            printf("Ошибка при считывании адреса\n");
            continue;
        }
        scanf("%lf %s %s %s", &weight, post_id, time_cr, time_d);

        if (strcmp(town, "Stop") == 0) {
            break;
        }

        mail new_mail;
        if(create_mail(&new_adress, weight, post_id, time_cr, time_d, &new_mail) != OK){
            printf("Ошибка создания отправления\n");
            continue;
        }
        if (add_mail_to_post(&my_post_office, new_mail) == OK) {
            printf("Отправление успешно добавлено.\n");
        } else {
            printf("Ошибка при добавлении отправления.\n");
        }
    }

    return 0;
}