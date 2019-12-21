#include "unixprog.h"

// Note that stdin2stdout.c works with binary files but this program does not
// When fgets and fputs hit a null byte they stop
int main() {
    char buf[UNIXPROG_MAXLEN];
    while (fgets(buf, UNIXPROG_MAXLEN, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            unixprog_sys_error_quit("Output error");
        }
    }
    if (ferror(stdin)) {
        unixprog_sys_error_quit("Input error");
    }
    // Note that in this program and stdin2stdout.c we don't close the streams since exit will clean up everything
    exit(0);
}