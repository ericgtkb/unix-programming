#include "unixprog.h"
#include <sys/wait.h>

void unixprog_print_exit(int status) {
    if (WIFEXITED(status)) {
        printf("Normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    } else if (WIFSTOPPED(status)) {
        printf("Child stopped, signal num,mber = %d\n", WSTOPSIG(status));
    }
}