#define _GNU_SOURCE
#define BUF_SIZE 1024

#define TRUE 1
#define FALSE 0

#include "tree.h"


int main(int argc, char * argv[]) {
    int hidden = TRUE;
    int size = FALSE;
    int indent = 0;
    if (argc < 2){ // check for no flags and no specified directory
        add_to_list(".", indent, TRUE, FALSE);
    }
    else{
        // RAISE FLAGS
        int x;
        for (x = 0; x < argc; x++) {
            if (strcmp(argv[x], "-a") == 0) { // raise hidden flag
                hidden = FALSE;
            }
            else if (strcmp(argv[x], "-s") == 0){ // raise size flag
                size = TRUE;
            }
        }

        int i;
        for (i = 0; i < argc; i++) { 
            if (!((strcmp(argv[i], "-a") == 0 || (strcmp(argv[i], "-s") == 0)))) {
                printf("%s\n", argv[i]);
                add_to_list(argv[i], 0, hidden, size);
            }
            printf("\n");
        }
    }
    return 0;
}

void add_to_list(char *name, int indent, int hidden, int size){
    arraylist *dlist;
    dlist = array_list_new(); // create an empty arraylist
    DIR *dir;
    struct dirent *files; // to get info on files

    if (!(dir = opendir(name))){ // MAKE SURE FILE CAN BE OPENED
        printf("directory cannot be opened \n");
        free_array_list(dlist);
        return;
    }
    while ((files = readdir(dir)) != NULL){ // GOES THROUGH EACH FILE IN DIR and adds name to the arraylist
        char *n = files -> d_name;
        int c;
        c = n[0];
        if (strcmp(n, ".") == 0 || strcmp(n, "..") == 0) // checks for symbolic links
            continue;
        if (hidden == TRUE && c == '.') // checks for hidden files 
            continue;
        char *obj = strdup(files -> d_name); 
        array_list_add_to_end(dlist, obj);
    }
    closedir(dir);
    q(dlist);
    int x;
    x = 0;
    while(x != dlist -> numitems) {
        char *entry = dlist ->data[x];
        int s;
        char *spacing = "|  ";
        for(s = 0; s < indent; s ++){
            printf("%s", spacing);
            s++;
        }
        printf("|--%s", entry);

        struct stat buffer;
        int check;
        char *item = (char*) malloc (strlen(name) + strlen(dlist -> data[x]) + 2);
        sprintf(item, "%s/%s", name, dlist->data[x]);
        check = lstat(item, &buffer);
        if (size == TRUE && check == 0){
            off_t size = buffer.st_size;
            printf(" [size: %lld]", (long long) size);
        }
        printf("\n");
        if(S_ISDIR(buffer.st_mode)){
            add_to_list(item, indent + 2, hidden, size);
        }
        x++;
        free(item);
    }
    free_array_list(dlist);
    return;
}

void q(arraylist *mylist) {
    qsort(mylist -> data, mylist -> numitems, sizeof(char *), compare);
}


arraylist *array_list_new() {
    arraylist *mylist;
    mylist = (arraylist *)malloc(sizeof(arraylist));
    mylist->capacity = 10;
    mylist->data = (char **)malloc(sizeof(char *) * mylist->capacity);
    memset(mylist -> data, '\0', sizeof(char *) * mylist->capacity);
    mylist->numitems = 0;
    return mylist;
}

void array_list_add_to_end(arraylist *mylist, char *new) {
    if (mylist -> numitems == mylist -> capacity) {
        mylist -> data = (char **) realloc (mylist -> data, sizeof(char *) * mylist -> capacity * 2);
        mylist -> capacity = (mylist -> capacity) * 2;
    }
    mylist -> data[mylist -> numitems] = new;
    (mylist -> numitems)++;
}

void free_array_list(arraylist *mylist){
    int i;
    for (i = 0; i < mylist -> capacity; i ++) {
        free(mylist -> data[i]);
    }
    free(mylist->data);
    free(mylist);
}

int compare(const void *a, const void *b) {
    const char **x = (const char **)a;
    const char **y = (const char **)b;
    return strcmp(*x, *y);
}
