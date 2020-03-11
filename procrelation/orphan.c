#include "unixprog.h"
#include <errno.h>

static void sig_hup(int signo) {
    printf("SIGHUP received, pid = %ld\n", (long) getpid());
}

static void print_ids(char *name) {
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n", name, (long) getpid(), (long) getppid(),
           (long) getpgrp(), (long) tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main() {
    char c;
    pid_t pid;
    print_ids("Parent");
    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid > 0) {  // Parent
        sleep(5);
    } else {  // Child
        print_ids("Child");
        signal(SIGHUP, sig_hup);  // Establish signal handler
        kill(getpid(), SIGTSTP);  // Stop ourself
        print_ids("Child");  // Print only if we're continued
        if (read(STDIN_FILENO, &c, 1) != 1) {
            printf("read error %d on controlling TTY\n", errno);
        }
    }
    exit(0);
}
