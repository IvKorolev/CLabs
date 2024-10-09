#include "operations.h"

int main (int argc, char* argv[]){
    double result;
    enum errors status_2 = second(&result, 1.0, 2, 2.0, 1.0, 1.0);
    if (status_2 == OK){
        printf("%lf\n", result);
    }

    if (first(4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0) == OK) {
        printf("Polygon is convex\n");
    } else {
        printf("Polygon is not convex\n");
    }

    if (first(4, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0) == OK) {
        printf("Polygon is convex\n");
    } else {
        printf("Polygon is not convex\n");
    }

    if (first(5, 0.0, 0.0, 2.0, 0.0, 1.0, 1.0, 0.0, 2.0, 2.0, 2.0) == OK) {
        printf("Polygon is convex\n");
    } else {
        printf("Polygon is not convex\n");
    }

    double *result1;
    int size;
    enum errors status = third(&result1, &size, 10, "45", "55", "297", "1", "703", "9", "8", NULL);
    if (status == OK) {
        printf("Числа Капрекара: ");
        for (int i = 0; i < size; i++) {
            printf("%.0f ", result1[i]);
        }
    }
    printf("\n");
    free(result1);
    return 0;
}