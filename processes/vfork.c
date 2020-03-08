#include "unixprog.h"

int global_var = 6;  // External variable in initialized data

int main() {
    int var;  // automatic variable on the stack
    pid_t pid;

    var = 88;
    printf("Before vfork\n");  // We don't flush stdout
    if ((pid = vfork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // Child
        global_var++;  // Modify parent's variables
        var++;
        _exit(0);
    }

    // Parent continues here
    printf("pid = %ld, global = %d, var = %d\n", (long) getpid(), global_var, var);

    exit(0);
}
