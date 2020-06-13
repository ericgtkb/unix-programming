#include "unixprog.h"
#include <pwd.h>

static void my_alarm(int signo) {
    struct passwd *rootptr;

    printf("In signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        unixprog_sys_error_quit("getpwnam(root) error");
        alarm(1);
    }
}

int main() {
    struct passwd *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for(;;) {
        if ((ptr = getpwnam("ericchen")) == NULL) {
            unixprog_sys_error_quit("getpwnam error");
        }
        if (strcmp(ptr->pw_name, "ericchen") != 0) {
            printf("Return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }
}
