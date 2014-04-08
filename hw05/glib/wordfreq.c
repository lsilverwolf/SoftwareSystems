#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <glib.h>
#include <err.h>

char *parse_file(char **input)
{    
    int c;
    char *intermediate = "trash2.txt";
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

int main ()
{
    //declarations
    char *input = "shortstory.txt";
    char *intermediate;
    int c;
    FILE *file;
    char *code;
    size_t n = 0;
    int num_of_words;
    int counter = 0;
    
    GHashTable *hashtable;
    guint *value;
    guint *unit;
    GList *allKeys;
    GList *allValues;
    guint** freq;
    char** str;
    char *parse_file(char **input);
    
    
    //This function takes the name of the text file that you hope to parse
    //(input) and returns the name of the name of the text file where it stored
    //the parsed version (intermediate).
    intermediate = parse_file(&input);
    
    //This function counts the number of words in the text file so that the
    //program knows how much memory to allocate for the array.
    //input: intermediate (the name of the text file where the parsed version of    
    //      the text can be found)
    //output: num_of_words (integer number of words in the parsed file)
    num_of_words = wordCount(intermediate);
    
    //Allocates memory for each word from the text file.
    char **words[num_of_words];
    for(int i = 0; i<num_of_words; i++) {
        words[i]=malloc(100 * sizeof(char *));
    }
    
    //Reads the file one line at a time and places each line in its own    
    //allocated section of an array.
    code = malloc(25*sizeof(char));
    file = fopen(intermediate, "r");
    while ((c = fgetc(file)) != EOF) {
        if ((char)c != '\n') {
            code[n++] = (char)c;
        }
        else {
            code[n] = '\0';  
            *words[counter] = strdup(code);
            n = 0;
            counter++;
        }
    }      

    fclose(file);

    //Creates a hash table for the frequency counting.    
    hashtable = g_hash_table_new(g_str_hash, g_str_equal);
    value = g_malloc(sizeof(guint));
    
    //This iterates through the array of words and determines if the word is    
    //already present in the hash table. If it is not, a new entry is created
    //and its frequency is listed as 1. If it is present, then the value 
    //increases by 1.
    for (int i = 0; i<(counter); i++) {
        value = (guint*) g_hash_table_lookup(hashtable, *words[i]);
        if (value == NULL) {
            unit = g_malloc(sizeof(guint));
            *(unit) = 1;
            g_hash_table_insert(hashtable, *words[i], unit);
        }
        else {
            (*value)++;
            g_hash_table_replace(hashtable, *words[i], value);
        }
    }
    
    //Prints out the words and their associated frequencies.
    guint  uniqueWords = g_hash_table_size(hashtable);
    printf("\nThere are %d unique words in this file.\n\n", uniqueWords);
    allKeys = g_hash_table_get_keys(hashtable);
    allValues = g_hash_table_get_values(hashtable);
    printf("Frequency:\tString\n");
    for (int i = 0; i<uniqueWords; i++) {
        freq = (guint **)allValues->data;
        str = (char **)allKeys->data;
        g_print("%d \t\t %s \n", *freq, str);
        allValues = allValues->next;
        allKeys = allKeys->next;
    }
    return 0;
}