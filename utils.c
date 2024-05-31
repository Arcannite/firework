#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getFileChars(char *filepath) {
    FILE *fd;
    fd = fopen(filepath, "r");
    if (!fd) {
        perror("The specified file was not found. Aborting.\n");
        exit(1);
    }

    // calculate file size
    size_t fileSize;
    fseek(fd, 0, SEEK_END);
    fileSize = ftell(fd);
    rewind(fd);

    // load stream into buffer
    char *buf = (char *) malloc(fileSize * sizeof(char));
    size_t ret_code = fread(buf, sizeof(buf), fileSize, fd);
    if (ret_code == fileSize) {
        buf[fileSize++] = '\0'; // just to make sure 
    }
    else if (ferror(fd))
        perror("Error reading file");
        exit(1);
    
    
    fclose(fd);
    
    return buf;
}