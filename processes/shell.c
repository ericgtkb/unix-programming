#include "unixprog.h"
#include <sys/wait.h>

static void sig_int(int signo);

int main() {
    char buf[MAXLEN];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        unixprog_sys_error_quit("Signal error");
    }

    printf("%% ");  // Shell prompt
    while (fgets(buf, MAXLEN, stdin) != NULL) {  // When we type end-of-file character fgets returns NULL
        if (buf[strlen(buf) - 1] == '\n') {
            // fgets returns a string terminated with '\n'. We change is to to a null character for execlp
            buf[strlen(buf) - 1] = 0;  // Replace newline with null
        }
        if ((pid = fork()) < 0) {
            // Call fork() to create a new process, a copy of the caller
            unixprog_sys_error_quit("Fork error");
        } else if (pid == 0) {  // Child
            execlp(buf, buf, (char *) 0);
            unixprog_error_return("Couldn't execute: %s", buf);
            exit(42);
        }

        // Parent
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            unixprog_sys_error_quit("waitpid error");
        }
        printf("%% ");
    }

    exit(0);
}

void sig_int(int signo) {
    printf("Interrupt\n%% ");
}
