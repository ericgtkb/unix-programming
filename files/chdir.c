#include "unixprog.h"

int main() {
    if (chdir("/tmp") < 0) {
        unixprog_sys_error_quit("chdir failed");
    }
    printf("chdir to /tmp succeeded\n");
    exit(0);
}
