#include "unixprog.h"

static void my_exit1();
static void my_exit2();

int main() {
    if (atexit(my_exit2) != 0) {
        unixprog_sys_error_quit("Can't register my_exit2");
    }

    if (atexit(my_exit1) != 0) {
        unixprog_sys_error_quit("Can't register my_exit1");
    }

    if (atexit(my_exit1) != 0) {
        unixprog_sys_error_quit("Can't register my_exit1");
    }
    // Note that these handlers are called in reverse order of their registration
    printf("main is done\n");

    // Note we use return not exit here;
    return 0;
}

static void my_exit1() {
    printf("First exit handler\n");
}

static void my_exit2() {
    printf("Second exit handler\n");
}

