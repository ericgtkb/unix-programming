#include "unixprog.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};
int main() {
    pid_t  pid;

    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // Child, specify pathname, specify environment
        if (execle("./echoall", "echoall", "myarg1", "MY ARG2",
                   (char *) 0, env_init) < 0) {
            unixprog_sys_error_quit("execle error");
        }
    }
    if (waitpid(pid, NULL, 0) < 0) {
        unixprog_sys_error_quit("wait error");
    }

    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) { // Specify filename, inherit environment
        // Modify the first argument to just "echoall" if echoall is in PATH
        if (execlp("./echoall", "echoall", "only 1 arg", (char *) 0) < 0) {
            unixprog_sys_error_quit("execlp error");
        }
    }

    exit(0);
}
