#include "unixprog.h"
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;


    // Normal termination
    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // Child
        exit(7);
    }

    if (wait(&status) != pid) { // Wait for child
        unixprog_sys_error_quit("wait error");
    }
    unixprog_print_exit(status);


    // Abort
    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // Child
        abort();  // Generates SIGABRT
    }

    if (wait(&status) != pid) { // Wait for child
        unixprog_sys_error_quit("wait error");
    }
    unixprog_print_exit(status);


    // Divide by 0 signal
    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // Child
        status /= 0;  // generates SIGFPE
    }

    if (wait(&status) != pid) { // Wait for child
        unixprog_sys_error_quit("wait error");
    }
    unixprog_print_exit(status);

    exit(0);
}
