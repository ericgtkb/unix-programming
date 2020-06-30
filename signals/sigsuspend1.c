#include "unixprog.h"

static void sig_int(int);

int main() {

    sigset_t newmask, oldmask, waitmask;

    unixprog_print_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGINT) error");
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

     // Block SIGINT and save current signal mask.
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        unixprog_sys_error_quit("SIG_BLOCK error");
    }

     // Critical region of code.
    unixprog_print_mask("in critical region: ");

    // Pause, allowing all signals except SIGUSR1.
    if (sigsuspend(&waitmask) != -1) {
        unixprog_sys_error_quit("sigsuspend error");
    }

    unixprog_sys_error_quit("after return from sigsuspend: ");

    // Reset signal mask which unblocks SIGINT.
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        unixprog_sys_error_quit("SIG_SETMASK error");
    }

    // And continue processing ...
    unixprog_print_mask("program exit: ");

    exit(0);
}

static void sig_int(int signo) {
    unixprog_print_mask("\nin sig_int: ");
}
