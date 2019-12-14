#include "unixprog.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;

    if (argc != 2) {
        fprintf(stderr, "Usage: ls directory_name\n");
        exit(42);
    }
    if ((dir = opendir(argv[1])) == NULL) {
        fprintf(stderr, "Can't open %s: ", argv[1]);
        unixprog_print_sys_error();
        exit(42);
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    exit(0);
}
