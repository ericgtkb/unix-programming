#include "unixprog.h"

unsigned int sleep2(unsigned int seconds);
static void sig_int(int signo);

int main() {
    unsigned int unslept;
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        unixprog_sys_error_quit("signal(SIGINT error");
    }
    unslept = sleep2(5);
    printf("sleep2 returned: %u\n", unslept);

    exit(0);
}

static void sig_int(int signo) {
    // sleep2 will interrupt this handler
    volatile int k = 0;  // Making sure compilers don't discard the loop.
    printf("\nsig_int starting\n");
    for (int i = 0; i < 300000; i++) {
        for (int j = 0; j < 4000; j++) {
            k += i *j;
        }
    }
    printf("sig_int finished\n");
}
