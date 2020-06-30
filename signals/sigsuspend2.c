#include "unixprog.h"

volatile sig_atomic_t quitflag;  // set nonzero by signal handler

static void sig_int(int signo) {  // one signal handler for SIGINT and SIGQUIT
    if (signo == SIGINT) {
        printf("\ninterrupt\n");
    } else if (signo == SIGQUIT) {
        quitflag = 1;  // set flag for main loop
    }
}

int main(void) {
    sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGINT) error");
    }
    if (signal(SIGQUIT, sig_int) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGQUIT) error");
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    // Block SIGQUIT and save current signal mask.
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        unixprog_sys_error_quit("SIG_BLOCK error");
    }

    while (quitflag == 0) {
        sigsuspend(&zeromask);
    }

    // SIGQUIT has been caught and is now blocked; do whatever.
    quitflag = 0;

    // Reset signal mask which unblocks SIGQUIT.
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        unixprog_sys_error_quit("SIG_SETMASK error");
    }

    exit(0);
}

