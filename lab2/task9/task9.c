#include "operations.h"

int main(int argc, char* argv[]){
    print_check_infinite_representation(3, 10, 0.5, 0.125, 0.3);
    print_check_infinite_representation(3, 8, 0.5, 0.125, 0.3);
    print_check_infinite_representation(3, 12, 0.5, 0.125, 0.3);
    print_check_infinite_representation(3, 4, 0.36, 0.125, 0.3);
    return 0;
}