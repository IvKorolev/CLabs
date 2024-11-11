#include "operations.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Error opening file");
        return 1;
    }

    int initial_size = 10;
    hash_table* map = create_table(initial_size);
    if (map == NULL) {
        fprintf(stderr, "Error creating hash table\n");
        fclose(input);
        return 1;
    }

    if (read_file(input, map) != OK) {
        fprintf(stderr, "Error reading file into hash table\n");
        delete_hash_table(map);
        fclose(input);
        return 1;
    }

    fclose(input);

    print_table(map);

    delete_hash_table(map);

    return 0;
}
