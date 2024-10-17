#include "operations.h"

int main() {
    const char *substring = "abc";

    find_in_files(substring, 2, "file1.txt", "file2.txt");

    return 0;
}