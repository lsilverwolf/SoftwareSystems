#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "parse_file.h"

char *parse_file(char **input)
{    
    int c;
    char *intermediate = "trash.txt";
    FILE *input_file;
    FILE *output_file = fopen(intermediate, "w");
    // NOTE: make this dynamic in the future!
    input_file = fopen(*input, "r");

    if (input_file == 0 || output_file == 0) {
        //fopen returns 0, the NULL pointer, on failure
        perror("File error\n");
        exit(-1);
    }
    else {
        int found_word = 0;
        while ((c =fgetc(input_file)) != EOF ) {
            //if it's an alpha, convert it to lower case
            if (isalpha(c)) {
                found_word = 1;
                c = tolower(c);
                fprintf(output_file,"%c",c);
            }
            else {
                if (found_word) {
                    fprintf(output_file,"\n");
                    found_word=0;
                }
            }
        }
    }
    fclose(input_file);
    fclose(output_file);
    return intermediate;
}