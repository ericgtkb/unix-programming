#include "unixprog.h"
#include <errno.h>

void make_temp(char *template);

int main() {
    // mkstemp changes the 6 X's
    char good_template[] = "/tmp/dirXXXXXX";  // On the stack
    char *bad_template = "/tmp/dirXXXXXX";  // On the heap

    printf("Trying to create the first temp file...\n");
    make_temp(good_template);
    printf("Trying to create the second temp file...\n");
    make_temp(bad_template);

    exit(0);
}

void make_temp(char *template) {
    int fd;
    struct stat statbuf;

    if ((fd = mkstemp(template)) < 0) {
        unixprog_sys_error_quit("Can't create temp file");
    }
    printf("Temp name = %s\n", template);
    close(fd);
    if (stat(template, &statbuf) < 0) {
        if (errno == ENOENT) {
            printf("File doesn't exist\n");
        } else {
            unixprog_sys_error_quit("stat failed");
        }
    } else {
        printf("File exists\n");
        unlink(template);
    }
}
