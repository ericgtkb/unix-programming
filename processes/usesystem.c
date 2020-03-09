#include "unixprog.h"

int main(int argc, char *argv[]) {
    int status;

    if (argc < 2) {
        unixprog_error_quit("Command-line argument required");
    }

    if ((status = system(argv[1])) < 0) {
        unixprog_sys_error_quit("system() error");
    }
    unixprog_pr_exit(status);

    exit(0);
}
