#include "unixprog.h"
#include <fcntl.h>

// The program truncates files reduces its size to zero without changing their access time or modification time.
int main(int argc, char *argv[]) {
    int fd;
    struct stat statbuf;
    struct timespec times[2];

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &statbuf) < 0) {
            unixprog_sys_error_return("%s: stat error", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
            unixprog_sys_error_return("%s: open error", argv[i]);
            continue;
        }

        // time[0] stores access time time[1] stores modification time
        // Seems to not work properly on macOS
#ifdef __APPLE__
        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;
#else
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;
#endif
        if (futimens(fd, times) < 0) {
            unixprog_sys_error_return("%s: futimens error", argv[i]);
        }
        close(fd);
    }
    exit(0);
}
