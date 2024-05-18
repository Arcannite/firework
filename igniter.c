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

    // load the file from memory, and parse it separately: leave IO ASAP
    // dynamic mem
    char *program = getFileChars(filepath);
    
    int progPtr = 0;
    int tokenPtr = 0;
    char currentChar;
    char tokenBuf[255];
    
    // start parsing
    do {
        currentChar = program[progPtr++];
        putchar(currentChar);
    }
    while (currentChar != '\0');

    free(program);

    return 0;
}
