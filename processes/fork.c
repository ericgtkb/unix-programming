#include "unixprog.h"


int global_var = 6;  // External variable in initialized data
char buf[] = "A write to stdout\n";


int main() {
    int var;  // automatic variable on the stack
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) -1) {
        unixprog_sys_error_quit("Write error");
    }
    printf("Before fork\n");  // We don't flush stdout
    if ((pid = fork()) < 0) {
        unixprog_sys_error_quit("fork error");
    } else if (pid == 0) {  // Child
        global_var++;  // Child gets a copy of everything
        var++;
    } else {  // Parent
        sleep(2);
    }

    printf("pid = %ld, global = %d, var = %d\n", (long) getpid(), global_var, var);

    exit(0);
}
