#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main ()
{
    int c;
//     char *input = argv[1];
    FILE *input_file;

    // NOTE: make this dynamic in the future!
    input_file = fopen("shortstory.txt", "r");

    if (input_file == 0)
    {
        //fopen returns 0, the NULL pointer, on failure
        perror("Cannot open input file\n");
        exit(-1);
    }
    else
    {
        int found_word = 0;

        while ((c =fgetc(input_file)) != EOF )
        {
            //if it's an alpha, convert it to lower case
            if (isalpha(c))
            {
                found_word = 1;
                c = tolower(c);
                putchar(c);
            }
            else {
                if (found_word) {
                    putchar('\n');
                    found_word=0;
                }
            }

        }
    }

    fclose(input_file);

    return 0;
}