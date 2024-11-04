#include "operations.h"

int main(){
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
    return 0;
}