#include "operations.h"

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Ошибка. Неправильное количество аргументов\n");
        return INVALID_INPUT;
    }
    int num;
    char choice;
    char pod[50];
    enum errors status1;
    Student * list = NULL;
    FILE* input = fopen(argv[1], "r");
    if (input == NULL){
        printf("Ошибка открытия входного файла\n");
        return INVALID_INPUT;
    }
    const char* input_filename = get_filename(argv[1]);
    const char* output_filename = get_filename(argv[2]);
    if (strcmp(input_filename, output_filename) == 0) {
        printf("Ошибка: входной и выходной файлы имеют одинаковые имена\n");
        fclose(input);
        return INVALID_INPUT;
    }
    int size = 0;
    enum errors status = create_list(input, &list, &size);
    if (status != OK){
        printf("Ошибка обработки файла\n");
        return INVALID_MEMORY;
    }
    printf("1 для поиска студентов\n"
           "2 для сортировки студентов\n"
           "3 вывести в файл фамилии и имена студентов, чей средний балл за все экзамены выше среднего\n"
           "балла за все экзамены по всем считанным из файла студентам.\n"
           "0 для завершения программы\n");
    printf("Введите действие: ");
    scanf("%d", &num);
    while(num != 0){
        switch(num){
            case 1:
                printf("\nВведите по чему искать студента\n"
                       "a - по id\n"
                       "b - по фамилии\n"
                       "c - по имени\n"
                       "d - по группе\n");
                printf("Введите флаг: ");
                scanf("%s", &choice);
                switch(choice){
                    case 'a':
                        printf("Введите id: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'a', size);
                        if (status1 == OK){
                            printf("Студент(ы) найдены, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    case 'b':
                        printf("Введите фамилию: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'b', size);
                        if (status1 == OK){
                            printf("Студент(ы) найдены, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    case 'c':
                        printf("Введите имя: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'c', size);
                        if (status1 == OK){
                            printf("Студент(ы) найдены, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    case 'd':
                        printf("Введите группу: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'd', size);
                        if (status1 == OK){
                            printf("Студент(ы) найдены, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    default:
                        printf("Ошибка, такого флага нет\n");
                        break;
                }
                break;
            case 2:
                printf("\nВведите по чему сортировать студентов\n"
                       "a - по id\n"
                       "b - по фамилии\n"
                       "c - по имени\n"
                       "d - по группе\n");
                printf("Введите флаг: ");
                scanf("%s", &choice);
                switch(choice){
                    case 'a':
                        printf("Введите id: ");
                        scanf("%s", pod);
                        status1 = sort(list, argv[2], pod, 'a', size);
                        if (status1 == OK){
                            printf("Студенты отсортированы, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    case 'b':
                        printf("Введите фамилию: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'b', size);
                        if (status1 == OK){
                            printf("Студенты отсортированы, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    case 'c':
                        printf("Введите имя: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'c', size);
                        if (status1 == OK){
                            printf("Студенты отсортированы, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    case 'd':
                        printf("Введите группу: ");
                        scanf("%s", pod);
                        status1 = search(list, argv[2], pod, 'd', size);
                        if (status1 == OK){
                            printf("Студенты отсортированы, проверьте выходной файл\n");
                        }
                        else{
                            printf("Не удалось найти ни одного студента\n");
                        }
                        break;
                    default:
                        printf("Ошибка, такого флага нет\n");
                        break;
                }
                break;
            case 3:
                break;
            default:
                printf("Такого флага нет в существующих\n");
                break;
        }
        printf("Введите действие:");
        scanf("%d", &num);
    }
    free_student_list(list, size);
    fclose(input);
    return 0;
}