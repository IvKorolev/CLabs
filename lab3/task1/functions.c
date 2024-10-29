#include "operations.h"

int sum(int num1, int num2) {
    int res = 0, carry = 0;
    res = num1 ^ num2;
    carry = (num1 & num2) << 1;
    while (carry)
    {
        int tmp = res;
        res = res ^ carry;
        carry = (tmp & carry) << 1;
    }
    return res;
}

int negative(int n) {
    return sum(~n, 1);
}

int subtraction(int a, int b) {
    return sum(a, negative(b));
}

enum errors first(long int num, int r, char** res, int* capacity, int* count, char* base, int* flag_negative) {
    *count = 0;
    int mask, digit;

    if(num < 0){
        num = negative(num);
        *flag_negative = 1;
    }
    do {
        if (*count >= *capacity){
            *capacity <<= 1;
            char* new_memory = (char*)realloc(*res, *capacity * sizeof(char));
            if(new_memory == NULL){
                return INVALID_MEMORY;
            }
            *res = new_memory;
        }
        mask = subtraction((1 << r), 1);
        digit = num & mask;
        (*res)[*count] = base[digit];
        *count = sum(*count, 1);

        num >>= r;
    } while(num > 0);
    return OK;
}

void print_num(int flag, char * res, int count, int base) {
    printf("Result for base 2^%d: ", base);
    if(flag) printf("-");
    for (int i = count - 1; i >= 0; i = subtraction(i, 1)) {
        printf("%c", res[i]);
    }
    printf("\n");
}