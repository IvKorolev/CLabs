#include "operations.h"

enum errors first(FILE* input, FILE* output){
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, input) != NULL){
        int count_spaces = 0;
        int length = strlen(buffer);
        for (int i = 0; i < length; i++){
            char symbol;
            symbol = buffer[i];
            if (isalpha(symbol)) {
                for (int j = 0; j < count_spaces; j++) {
                    fputc(' ', output);
                }
                fputc(symbol, output);
                fputc('\n', output);
            }
            else if (symbol == '('){
                count_spaces += 1;
            }
            else if (symbol == ')'){
                count_spaces -= 1;
            }
        }
    }
    return OK;
}