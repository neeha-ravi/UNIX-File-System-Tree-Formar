#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <math.h>
#include <sys/stat.h>


char *remove_leading(char *str);
void remove_trailing(char *str);
void get_args(char *str, char *args[]);
char *remove_whitespace(char *str);
char *get_cwd();
void print_directory(const char *name, int indent);
void add_to_list(char *name, int indent, int hidden, int size);
static int compare(const void* a, const void* b);

typedef struct arraylist arraylist;

struct arraylist{
    int capacity;
    int numitems;
    char ** data ;
};

arraylist *array_list_new();

void q(arraylist *mylist);

void array_list_add_to_end(arraylist *mylist, char *new);

void print_array_list(arraylist *mylist, int indent);

void free_array_list(arraylist *mylist);