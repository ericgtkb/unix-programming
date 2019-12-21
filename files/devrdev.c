#include "unixprog.h"

int main(int argc, char *argv[]) {
    struct stat statbuf;

    for (int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (stat(argv[i], &statbuf) < 0) {
            unixprog_sys_error_return("stat error");
            continue;
        }
        printf("dev = %d/%d", major(statbuf.st_dev), minor(statbuf.st_dev));
        if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)) {
            printf(" (%s) rdev = %d/%d", (S_ISCHR(statbuf.st_mode)) ? "character" : "block",
                   major(statbuf.st_rdev), minor(statbuf.st_rdev));
        }
        printf("\n");
    }
    exit(0);
}
