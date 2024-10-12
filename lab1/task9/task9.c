#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <time.h>

enum errors {
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OVERFLOW,
    OK,
};

enum errors str_to_int(const char *x, long int *res) {
    char symbol;
    if (sscanf(x, "%ld%c", res, &symbol) != 1) {
        return INVALID_INPUT;
    }

    if (abs(*res) >= INT_MAX || abs(*res) <= INT_MIN) {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors swap_max_and_min(int arr[], long int a, long int b) {
    int max_index = 0, min_index = 0;
    for (int i = 1; i < 20; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    int temp = arr[max_index];
    arr[max_index] = arr[min_index];
    arr[min_index] = temp;
    return OK;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_closest(int value, int* B, int B_size) {
    int left = 0;
    int right = B_size - 1;
    int closest = B[0];

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (B[mid] == value) {
            return B[mid];
        }

        if (abs(B[mid] - value) < abs(closest - value)) {
            closest = B[mid];
        }

        if (B[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return closest;
}

int main(int argc, char* argv[]) {
    int arguments = argc;
    switch (arguments) {
        case 3: {
            long int a, b;
            if (str_to_int(argv[1], &a) != OK || str_to_int(argv[2], &b) != OK) {
                printf("Ошибка ввода аргументов\n");
                return INVALID_INPUT;
            }
            if (a >= b) {
                printf("Ошибка диапозона\n");
                return INVALID_INPUT;
            }
            srand(time(NULL));
            int result[20];
            for (int i = 0; i < 20; i++) {
                result[i] = rand() % (b - a + 1) + a;
                printf("%d ", result[i]);
            }
            printf("\n");
            swap_max_and_min(result, a, b);
            for (int i = 0; i < 20; i++) {
                printf("%d ", result[i]);
            }
            printf("\n");
            break;
        }
        case 1: {
            srand(time(NULL));

            int A_size = rand() % (10000 - 10 + 1) + 10;
            int B_size = rand() % (10000 - 10 + 1) + 10;

            int* A = (int*)malloc(A_size * sizeof(int));
            int* B = (int*)malloc(B_size * sizeof(int));
            int* C = (int*)malloc(A_size * sizeof(int));

            if (!A || !B || !C) {
                printf("Ошибка выделения памяти\n");
                free(A);
                free(B);
                free(C);
                return INVALID_MEMORY;
            }
            for (int i = 0; i < A_size; i++) {
                A[i] = rand() % 2001 - 1000;
                printf("A[%d] = %d\n", i, A[i]);
            }

            printf("\n");

            for (int i = 0; i < B_size; i++) {
                B[i] = rand() % 2001 - 1000;
                printf("B[%d] = %d\n", i, B[i]);
            }

            qsort(B, B_size, sizeof(int), compare);

            printf("\nОтсортированный массив B:\n");
            for (int i = 0; i < B_size; i++) {
                printf("%d ", B[i]);
            }
            printf("\n");

            for (int i = 0; i < A_size; i++) {
                int closest = find_closest(A[i], B, B_size);
                C[i] = A[i] + closest;
                printf("C[%d] = %d ближайший элемент %d из B\n", i, C[i], closest);
            }

            free(A);
            free(B);
            free(C);
            break;
        }
        default:
            printf("Ошибка. Неправильное количество аргументов\n");
            return INVALID_INPUT;
    }
    return 0;
}
