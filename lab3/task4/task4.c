#include "operations.h"

int main(int argc, char* argv[]){

    post my_post_office;
    int num;
    char town[50], street[50], korpus[50], index[50];
    int house_number, apartment;
    double weight;
    char post_id[15];
    char time_cr[100];
    char time_d[100];

    printf("\nСоздайте почтовое отделение: введите его адрес (город, ул, дом, корпус, номер кв, индекс)\n");
    printf("Введите город: ");
    scanf("%49s", town);
    printf("Введите улицу: ");
    scanf("%49s", street);
    printf("Введите Номер дома: ");
    scanf("%d", &house_number);
    printf("Введите корпус: ");
    scanf("%49s", korpus);
    printf("Введите номер квартиры: ");
    scanf("%d", &apartment);
    printf("Введите индекс (6 цифр): ");
    scanf("%6s", index);

    if (create_post(town, street, house_number, korpus, apartment, index, &my_post_office) != OK) {
        printf("Ошибка при создании почтового отделения.\n");
        return 1;
    }

    printf("1 - для создания посылки\n"
           "2 - для удаления посылки\n"
           "3 - для поиска посылки по идентификатору\n"
           "4 - для сортировки\n"
           "5 - для поиска всех доставленных отправлений\n"
           "6 - для поиска всех просроченных посылок\n"
           "0 - для завершения программы\n");

    printf("Введите значение: ");
    scanf("%d", &num);
    while(num != 0){
        switch(num){

            case 1:

                adress new_adress;
                mail new_mail;

                printf("\nВведите адрес, по которому хотите отправить посылку\n");
                printf("Введите город: ");
                scanf("%49s", town);
                printf("Введите улицу: ");
                scanf("%49s", street);
                printf("Введите Номер дома: ");
                scanf("%d", &house_number);
                printf("Введите корпус: ");
                scanf("%49s", korpus);
                printf("Введите номер квартиры: ");
                scanf("%d", &apartment);
                printf("Введите индекс (6 цифр): ");
                scanf("%6s", index);
                if (create_adress(town, street, house_number, korpus, apartment, index, &new_adress) != OK){
                    printf("Ошибка при считывании адреса\n");
                    break;
                }

                printf("\nТеперь введите данные посылки\n");
                printf("Введите вес посылки: ");
                scanf("%lf", &weight);

                printf("Введите почтовый идентификатор (14 символов): ");
                scanf("%14s", post_id);

                while (getchar() != '\n');
                printf("Введите время создания (формат dd:MM:yyyy hh:mm:ss): ");
                fgets(time_cr, sizeof(time_cr), stdin);

                printf("Введите время вручения (формат dd:MM:yyyy hh:mm:ss): ");
                fgets(time_d, sizeof(time_d), stdin);
                time_d[strcspn(time_d, "\n")] = '\0';

                if(create_mail(&new_adress, weight, post_id, time_cr, time_d, &new_mail) != OK){
                    printf("Ошибка создания отправления\n");
                    break;
                }
                if (add_mail_to_post(&my_post_office, new_mail) != OK) {
                    printf("Ошибка при добавлении отправления.\n");
                    break;
                }
                printf("Отправление успешно создано и добавлено\n");
                break;

            case 2:
                printf("Введите ID посылки (14 символов):\n");
                scanf("%14s", post_id);
                enum errors status2 = remove_mail(&my_post_office, post_id);
                if (status2 != OK){
                    printf("Ошибка удаления посылки\n");
                }
                else printf("Посылка удалена\n");

                break;

            case 3:
                mail found;
                printf("Введите ID посылки (14 символов):\n");
                scanf("%14s", post_id);
                enum errors status3 = find_mail(&my_post_office, post_id, &found);
                if (status3 != OK){
                    printf("Ошибка поиска посылки\n");
                }
                else{
                    printf("Посылка найдена:\n");
                    print_mail(&found);
                }
                break;

            case 4:
                enum errors status4 = sort(&my_post_office);
                if (status4 == OK){
                    printf("Отправления успешно отсортированы\n");
                }
                else printf("Произошла ошибка при сортировке\n");
                for(int i = 0; i < my_post_office.size; i++){
                    print_mail(&my_post_office.mass[i]);
                }
                break;

            case 5:
                printf("Доставленные посылки\n");
                for(int i = 0; i < my_post_office.size; i++) {
                    if (is_deliveried(&my_post_office.mass[i])) {
                        print_mail(&my_post_office.mass[i]);
                    }
                }
                break;

            case 6:
                printf("Недоставленные посылки\n");
                for(int i = 0; i < my_post_office.size; i++) {
                    if (!is_deliveried(&my_post_office.mass[i])) {
                        print_mail(&my_post_office.mass[i]);
                    }
                }
                break;

            default:
                printf("Такого флага нет\n");
                break;
        }
        printf("Введите значение: ");
        scanf("%d", &num);
    }

    return 0;
}