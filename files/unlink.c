#include "unixprog.h"
#include <fcntl.h>

int main() {
    if (open("tempfile", O_RDWR) < 0) {
        unixprog_sys_error_quit("open error");
    }
    if (unlink("tempfile") < 0) {
        unixprog_sys_error_quit("unlink error");
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    exit(0);
}
