#include "unixprog.h"
#include <sys/wait.h>

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {
        // Modify the path to wherever testinterp is located
        // Note that in the output we see the pathname instead of just "testinterp"
        if (execl("/Users/ericchen/Projects/unix-programming/processes/testinterp", "testinterp", "myarg1", "MY ARG2", (char *) 0) < 0) {
            unixprog_sys_error_quit("execl error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        unixprog_sys_error_quit("waitpid error");
    }

    exit(0);
}
