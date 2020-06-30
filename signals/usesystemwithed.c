#include "unixprog.h"

int system(const char*);

static void sig_int(int signo) {
    printf("Caught SIGINT\n");
}

static void sig_chld(int signo) {
    printf("Caught SIGCHLD\n");
}

int main() {
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGINT) error");
    }
    if (signal(SIGCHLD, sig_chld) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGCHLD) error");
    }
    if (system("/bin/ed") < 0) {
        unixprog_sys_error_quit("system() error");
    }
    exit(0);
}

