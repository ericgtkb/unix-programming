#include "unixprog.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0) {  // FILE_MODE defined in unixprog.h
        unixprog_sys_error_quit("creat error");
    }
    if (write(fd, buf1, 10) != 10) {
        unixprog_sys_error_quit("buf1 write error");
    }
    // Offset now = 10
    if (lseek(fd, 16384, SEEK_SET) == -1) {
        unixprog_sys_error_quit("lseek error");
    }
    // Offset now = 16384
    if (write(fd, buf2, 10) != 10) {
        unixprog_sys_error_quit("buf2 write error");
    }
    // Offset now = 16394

    exit(0);
}
