#include "unixprog.h"

int main() {
    int c;
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            unixprog_sys_error_quit("Output error");
        }
    }
    if (ferror(stdin)) {
        unixprog_sys_error_quit("Input error");
    }
    exit(0);
}