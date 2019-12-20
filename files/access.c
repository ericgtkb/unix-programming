#include "unixprog.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        unixprog_error_quit("Usage: access <pathname>");
    }
    if (access(argv[1], R_OK) < 0) {
        unixprog_sys_error_return("Access error for %s", argv[1]);
    } else {
        printf("Read access OK\n");
    }
    if (open(argv[1], O_RDONLY) < 0) {
        unixprog_sys_error_return("Open error for %s", argv[1]);
    } else {
        printf("Open for reading OK\n");
    }
    exit(0);
}
