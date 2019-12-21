#include "unixprog.h"

// Change directory, and print working directory
int main(int argc, char *argv[]) {
    if (argc != 2) {
        unixprog_error_quit("Usage: getcwd directory_name\n");
    }

    char *cwd;
    size_t size;

    if (chdir(argv[1]) < 0) {
        unixprog_sys_error_quit("chdir failed");
    }

    cwd = path_alloc(&size);  // Defined in unixprog.h
    if (getcwd(cwd, size) == NULL) {
        unixprog_sys_error_quit("getcwd failed");
    }
    printf("cwd = %s\n", cwd);
    exit(0);
}
