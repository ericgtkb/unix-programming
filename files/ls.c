#include "unixprog.h"
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;

    if (argc != 2) {
        unixprog_error_quit("Usage: ls directory_name");
    }
    if ((dir = opendir(argv[1])) == NULL) {
        unixprog_sys_error_quit("Can't open %s", argv[1]);
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    exit(0);
}
