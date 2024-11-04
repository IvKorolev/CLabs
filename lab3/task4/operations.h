#ifndef CLABS_OPERATIONS_H
#define CLABS_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_t unsigned long long

enum errors{
    INVALID_INPUT,
    INVALID_MEMORY,
    OK,
};

typedef struct string{
    char* array;
    int length;
}String;

typedef struct adress{
    String town;
    String street;
    int house_number;
    String korpus;
    int apartment;
    String index;
}adress;

typedef struct mail{
    adress adr;
    double weight;
    String post_id;
    String time_of_creation;
    String time_of_delivery;
}mail;

typedef struct post{
    adress* this_building;
    mail* mass;
    int size;
}post;

enum errors create_str(char* input, String* result);
enum errors delete_str(String* input);
enum errors compare_srt(String* first, String* second, int *result);
enum errors equivalence(String* first, String* second, int* flag);
enum errors copy_to_existing(String* first, String* second);
String* copy_to_new(String* first);
enum errors concatenate(String* first, String* second);

enum errors create_post(char* town, char* street, int house_number, char* korpus, int apartment, char* index, post* post_office);
enum errors create_adress(char* town, char* street, int house_number, char* korpus, int apartment, char* index, adress* new_adress);
enum errors create_mail(adress* adr, double weight, char* post_id, char* time_cr, char* time_d, mail* new_mail);
enum errors add_mail_to_post(post* post_office, mail new_mail);
enum errors remove_mail(post* post, const char* post_id);
enum errors find_mail(post* Post, const char* post_id, mail* res);
enum errors print_mail(mail* Mail);


#endif //CLABS_OPERATIONS_H
