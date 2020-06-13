#include "unixprog.h"

static void sig_alrm(int signo);

int main() {
    int n;
    char line[UNIXPROG_MAXLEN];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGALRM) error");
    }
    alarm(3);  // Race condition. read may block
    // On macOS alarm seems to be blocked by read all the time.
    if ((n = read(STDIN_FILENO, line, UNIXPROG_MAXLEN)) < 0) {
        unixprog_sys_error_quit("read error");
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);

    exit(0);
}

static void sig_alrm(int signo) {
    // Just return to interrupt read.
}
