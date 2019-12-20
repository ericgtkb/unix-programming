#include "unixprog.h"

int main() {
    struct stat statbuf;
    // Modify the access of the files created by the umask.c program

    // Turn on set-group-ID and turn off group-execute
    if (stat("foo", &statbuf) < 0) {
        unixprog_sys_error_quit("stat error for foo");
    }
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
        unixprog_sys_error_quit("chmod error for foo");
    }

    // Set absolute mode to "rw-r--r--"
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
        unixprog_sys_error_quit("chmod error for bar");
    }
    exit(0);
}
