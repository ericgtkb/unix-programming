#include "unixprog.h"
#include <errno.h>

void unixprog_print_sys_error() {
    fprintf(stderr, "%s\n", strerror(errno));
}
