#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char **argv) {

    // only support one input file with no options for now
    if (argc != 2) {
        printf("Usage: igniter <name of file to be compiled>");
        return 1;
    }

    char *filepath = argv[1];

    // dynamic mem
    char *program = getFileChars(filepath);
    puts(program);
    free(program);

    return 0;
}
