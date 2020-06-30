#include "unixprog.h"

static volatile sig_atomic_t sigflag;  // Set nonzero by sig handler
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) {
    // One handler for both SIGUSR1 and SIGUSR2
    sigflag = 1;
}


void unixprog_tell_wait() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGUSR1) error");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGUSR2) error");
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    // Block SIGUSR1 and SIGUSR2, and save the current mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        unixprog_sys_error_quit("SIG_BLOCK error");
    }
}


void unixprog_tell_parent(pid_t pid) {
    kill(pid, SIGUSR2);  // Tell parent we are done
}


void unixprog_wait_parent() {
    while (sigflag == 0) {
        sigsuspend(&zeromask);  // Wait for parent
    }

    sigflag = 0;
    // Reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        unixprog_sys_error_quit("SIG_SETMASK error");
    }
}


void unixprog_tell_child(pid_t pid) {
    kill(pid, SIGUSR1);  // Tell child we are done
}


void unixprog_wait_child() {
    while (sigflag == 0) {
        sigsuspend(&zeromask);  // Wait for child
    }

    sigflag = 0;
    // Reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        unixprog_sys_error_quit("SIG_SETMASK error");
    }
}

