#include "unixprog.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int val;
    if (argc != 2) {
        unixprog_error_quit("Usage: fileflags <descriptor#>");
    }

    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        unixprog_sys_error_quit("fcntl error for fd %d", atoi(argv[1]));
    }

    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("Read only");
            break;
        case O_WRONLY:
            printf("Write only");
            break;
        case O_RDWR:
            printf("Read write");
            break;
        default:
            unixprog_sys_error_dump("Unknown access mode");
    }

    if (val & O_APPEND) {
        printf(", append");
    }
    if (val & O_NONBLOCK) {
        printf(", nonblocking");
    }
    if (val & O_SYNC) {
        printf(", synchronous writes");
    }
// Not required for both macOS and Linux
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC) {
        printf(", synchronous writes");
    }
#endif

    putchar('\n');
    exit(0);
}
