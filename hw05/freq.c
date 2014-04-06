#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <glib.h>
#include <err.h>

int main ()
{
    int c;
    int d;
//     char *input = argv[1];
    FILE *file;
    GList* list = NULL;
    char *code;
    size_t n = 0;
    int counter = 0;
    int beginning = 0;
    GHashTable *hashtable = g_hash_table_new(g_str_hash, g_str_equal);

    // NOTE: make this dynamic in the future!
    file = fopen("parsedstory.txt", "r");

    if (file == NULL) {
		perror("Cannot open input file\n");
        exit(-1);
    }
    
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);
    
    while ((c = fgetc(file)) != EOF) {
        if ((char)c == '\n') {
            counter++;
        }
    }
    
    char **words[counter];
    for(int i = 0; i<counter; i++) {
        words[i]=malloc(100 * sizeof(char *));
    }
    
    counter = 0;
    fclose(file);
    
    file = fopen("parsedstory.txt", "r");
    while ((c = fgetc(file)) != EOF) {
        if ((char)c != '\n') {
            code[n++] = (char)c;
        }
        else {
            code[n] = '\0';  
            *words[counter] = strdup(code);
//             list = g_list_prepend(list, code);
            n = 0;
            counter++;
        }
    }      

    fclose(file);
    
    guint *value;
    value = g_malloc(sizeof(guint));
    guint *unit;
    
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
    
    guint  uniqueWords = g_hash_table_size(hashtable);
    printf("\nThere are %d unique words in this file.\n\n", uniqueWords);
    GList *allKeys = g_hash_table_get_keys(hashtable);
    GList *allValues = g_hash_table_get_values(hashtable);
    printf("Frequency:\tString\n");
    for (int i = 0; i<uniqueWords; i++) {
        guint** freq = (guint **)allValues->data;
        char** str = (char **)allKeys->data;
        printf("%d \t\t %s \n", *freq, str);
        allValues = allValues->next;
        allKeys = allKeys->next;
    }
    return 0;
}