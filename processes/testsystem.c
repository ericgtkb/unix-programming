#include "unixprog.h"

int main() {
    int status;

    if ((status = system("date")) < 0) {
        unixprog_sys_error_quit("system() error");
    }
    unixprog_print_exit(status);

    if ((status = system("nosuchcommand")) < 0) {
        unixprog_sys_error_quit("system() error");
    }
    unixprog_print_exit(status);

    if ((status = system("who; exit 44")) < 0) {
        unixprog_sys_error_quit("system() error");
    }
    unixprog_print_exit(status);
    exit(0);
}
