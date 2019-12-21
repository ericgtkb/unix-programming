#include "unixprog.h"
#include <errno.h>
#include <limits.h>

// path_max max bytes in pathname
#ifdef PATH_MAX
static long path_max = PATH_MAX;
#else
static long path_max = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

// If PATH_MAX is indeterminate, this is the guess, no guarantee this is adequate
#define PATH_MAX_GUESS 1024

char *unixprog_path_alloc(size_t *path_size) {
    // Also return allocated size to path_size
    char *path;
    size_t size;

    if (posix_version == 0) {
        posix_version = sysconf(_SC_VERSION);
    }
    if (xsi_version == 0) {
        xsi_version = sysconf(_SC_XOPEN_VERSION);
    }

    if (path_max == 0) {
        errno = 0;
        if ((path_max = pathconf("/", _PC_PATH_MAX)) < 0) {  // Returns max bytes in relative pathname
            if (errno == 0) {
                path_max = PATH_MAX_GUESS;  // It's indeterminate
            } else {
                unixprog_sys_error_quit("pathconf error for _PC_PATH_MAX");
            }
        } else {
            path_max++;  // Add one since it's relative to root
        }
    }

    // Before POSIX.1-2001 or XPG3, PATH_MAX may not include the terminating null byte.
    if ((posix_version < 2001112L) && (xsi_version < 4)) {
        size = path_max + 1;
    } else {
        size = path_max;
    }

    if ((path = malloc(size)) == NULL) {
        unixprog_sys_error_quit("malloc error for pathname");
    }

    if (path_size != NULL) {
        *path_size = size;
    }
    return path;
}
