#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getFileChars(char *filepath) {
    FILE *fptr;
    fptr = fopen(filepath, "r");
    if (!fptr) {
        perror("The specified file was not found. Aborting.\n");
        exit(1);
    }

    // calculate file size
    size_t fileSize;
    fseek(fptr, 0, SEEK_END);
    fileSize = ftell(fptr);
    rewind(fptr);

    // load stream into buffer
    char *buf = (char *) malloc(fileSize * sizeof(char));
    size_t ret_code = fread(buf, sizeof(buf), fileSize, fptr);
    if (ret_code == fileSize) {
        buf[fileSize++] = '\0'; // just to make sure 
    }
    else {
        if (feof(fptr))
            printf("Error reading file: unexpected end of file\n");
        else if (ferror(fptr))
            perror("Error reading file");
    }
    
    fclose(fptr);
    
    return buf;
}