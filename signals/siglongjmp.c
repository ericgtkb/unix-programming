#include "unixprog.h"
#include <setjmp.h>
#include <time.h>

static void sig_usr1(int signo);
static void sig_alrm(int signo);

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main() {
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGUSR1) error");
    }
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGALRM) error");
    }

    unixprog_print_mask("Starting main: ");

    if (sigsetjmp(jmpbuf, 1)) {
        unixprog_print_mask("Ending main: ");
        exit(0);
    }

    canjump = 1;

    for(;;) {
        pause();
    }

    exit(0);
}

static void sig_usr1(int signo) {
    time_t starttime;

    if (canjump == 0) {
        return;  // Unexpected signal, ignore
    }

    unixprog_print_mask("Starting sig_usr1: ");

    alarm(3);  // SIGALRM in 3 seconds
    starttime = time(NULL);
    for (;;) {
        if (time(NULL) > starttime + 5) {  // Busy wait for 5 seconds
            break;
        }
    }
    unixprog_print_mask("Finishing sig_usr1: ");
    canjump = 0;
    siglongjmp(jmpbuf, 1);  // jump back to main, don't return
}

static void sig_alrm(int signo) {
    unixprog_print_mask("In sig_alrm: ");
}
