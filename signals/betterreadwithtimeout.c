#include "unixprog.h"
#include <setjmp.h>

static void sig_alrm(int signo);
static jmp_buf env_alrm;


int main() {
    int n;
    char line[UNIXPROG_MAXLEN];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGALRM) error");
    }
    if (setjmp(env_alrm) != 0) {
        unixprog_error_quit("read timeout");
    }
    alarm(3);
    if ((n = read(STDIN_FILENO, line, UNIXPROG_MAXLEN)) < 0) {
        unixprog_sys_error_quit("read error");
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alrm(int signo) {
    longjmp(env_alrm, 1);
}
