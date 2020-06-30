#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>


// system with no signal handling...

int system(const char *cmdstring) {
    pid_t pid;
    int status;

    if (cmdstring == NULL) {
        return -1;
    }
    if ((pid =fork()) < 0) {
        status = -1;  // Probably out of processes
    } else if (pid == 0) {
        // child
        execl("/bin/bash", "bash", "-c", cmdstring, (char *) 0);
        _exit(42);  // execl error
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;  // error other than eintr from waitpid()
                break;
            }
        }
    }
    return status;
}
