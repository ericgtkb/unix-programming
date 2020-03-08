#include "unixprog.h"
#include <sys/wait.h>

// Prevent child from becoming a zombie, call fork twice
int main() {

    pid_t pid;

    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // First child
        if ((pid = fork()) < 0) {
            unixprog_sys_error_quit("fork error");
        } else if (pid > 0) {  // Parent from second fork == first child
            exit(0);  // Call exit right after a successful second fork
        }
        // We are now in second child. Our parent becomes init as soon as our real parent calls exit().
        // Here's where we'd continue executing, knowing that when we're done, init will reap our status.
        sleep(2);
        printf("Second child, parent pid = %ld\n", (long) getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid) {
        unixprog_sys_error_quit("waitpid error");
    }

    // We're in the parent (the original process). We continue executing, knowing that
    // we're not the parent of the second child.

    exit(0);
}
