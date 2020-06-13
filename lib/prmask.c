#include "unixprog.h"
#include <errno.h>

void print_mask(const char *str) {
    sigset_t sigset;
    int errno_save;

    errno_save = errno;  // can be called by signal handlers

    if (sigprocmask(0, NULL, &sigset) < 0) {
        unixprog_error_return("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT)) {
            printf(" SIGINT");
        }
        if (sigismember(&sigset, SIGQUIT)) {
            printf(" SIGQUIT");
        }
        if (sigismember(&sigset, SIGUSR1)) {
            printf(" SIGUSR1");
        }
        if (sigismember(&sigset, SIGALRM)) {
            printf(" SIGALRM");
        }

        // Other signals
        printf("\n");
    }

    errno = errno_save;  // Restore errno
}
