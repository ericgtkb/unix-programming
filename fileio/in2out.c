#include "unixprog.h"

#define BUFFSIZE 4096

int main() {
    int n;
    char buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            unixprog_sys_error_quit("Write error");
        }
    }
    if (n < 0) {
        unixprog_sys_error_quit("Read error");
    }
    exit(0);
}