#include <stdio.h>
#include <fcntl.h>
#include "wordCount.h"

int wordCount(char *intermediate) 
{
    int c;
    int counter = 0;
    FILE *file;
    file = fopen(intermediate, "r");
    if (file == NULL) {
		perror("Cannot open input file\n");
        exit(-1);
    }
        
    while ((c = fgetc(file)) != EOF) {
        if ((char)c == '\n') {
            counter++;
        }
    }
    return counter;
}