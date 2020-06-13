#include "unixprog.h"

static void sig_usr(int);

int main() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        unixprog_sys_error_quit("Can't catch SIGUSR1");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        unixprog_sys_error_quit("Can't catch SIGUSR2");
    }
    for (;;) {
        pause();
    }
}

static void sig_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("Received SIGUSR1\n");
    } else if (signo == SIGUSR2) {
        printf("Received SIGUSR2\n");
    } else {
        unixprog_sys_error_dump("Received signal %d\n", signo);
    }
}