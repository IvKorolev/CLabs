#include "operations.h"

void computeLPSArray(const char *substring, int M, int *lps) {
    int length = 0;
    int i = 1;
    lps[0] = 0;

    while (i < M) {
        if (substring[i] == substring[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(const char *substring, const char *str, int line_number, const char *file_path) {
    int M = strlen(substring);
    int N = strlen(str);

    int lps[M];
    computeLPSArray(substring, M, lps);

    int i = 0;
    int j = 0;

    while (i < N) {
        if (substring[j] == str[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("Файл: %s, строка: %d, символ: %d\n", file_path, line_number, i - j + 1);
            j = lps[j - 1];
        } else if (i < N && substring[j] != str[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

void find_in_files(const char *substring, int file_count, ...) {
    va_list args;
    va_start(args, file_count);

    for (int f = 0; f < file_count; f++) {
        const char *file_path = va_arg(args, const char*);
        FILE *file = fopen(file_path, "r");

        if (file == NULL) {
            printf("Ошибка при открытии файла: %s\n", file_path);
            continue;
        }

        char buffer[BUFFER_SIZE];
        int line_number = 1;

        while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
            KMPSearch(substring, buffer, line_number, file_path);
            line_number++;
        }

        fclose(file);
    }

    va_end(args);
}