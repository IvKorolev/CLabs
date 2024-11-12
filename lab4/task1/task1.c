#include "operations.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return INVALID_INPUT;
    }

    FILE* output = fopen("output.txt", "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output file\n");
        fclose(input);
        return INVALID_INPUT;
    }

    int initial_size = 128;
    hash_table* map = create_table(initial_size);
    if (map == NULL) {
        fprintf(stderr, "Error creating hash table\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    if (process_file(input, output, map) != OK) {
        fprintf(stderr, "Error processing file\n");
        delete_hash_table(map);
        fclose(input);
        fclose(output);
        return 1;
    }

    fclose(input);
    fclose(output);

    print_table(map);

    check_and_resize_table(&map);

    printf("\nAfter resizing (if applicable):\n");
    print_table(map);

    delete_hash_table(map);

    return 0;
}
