#include "operations.h"

enum errors first(FILE* input, FILE* output){
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, input) != NULL){
        int count_spaces = 0;
        int length = strlen(buffer);
        for (int i = 0; i < length; i++){
            char symbol;
            symbol = buffer[i];
            switch(symbol){
                case '(':
                    count_spaces += 1;
                    break;
                case ')':
                    count_spaces -= 1;
                    break;
                case ' ':
                    continue;
                case ',':
                    continue;
                default:
                    for (int j = 0; j < count_spaces; j++) {
                        fputc(' ', output);
                    }
                    fputc(symbol, output);
                    fputc('\n', output);
            }
        }
    }
    return OK;
}