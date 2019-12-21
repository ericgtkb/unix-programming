#include "unixprog.h"
#include <errno.h>
#include <stdarg.h>

static void print_with_sys_error(const char *format, va_list ap);

// Fatal error unrelated to a system call
// Print error message and exit
void unixprog_error_quit(const char *format, ...) {  // TODO: fix it so that we don't need '\n'
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    exit(42);
}

// Nonfatal error related to a system call
// Print error message and return
void unixprog_sys_error_return(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_with_sys_error(format, ap);
    va_end(ap);
}

// Fatal error related to a system call
// Print error message and exit
void unixprog_sys_error_quit(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_with_sys_error(format, ap);
    va_end(ap);
    exit(42);
}

// Fatal error related to a system call
// Print error message dump core and exit
void unixprog_sys_error_dump(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_with_sys_error(format, ap);
    va_end(ap);
    abort();  // Dump core and terminate
}

static void print_with_sys_error(const char *format, va_list ap) {
    char buf[UNIXPROG_MAXLEN];
    vsnprintf(buf, UNIXPROG_MAXLEN - 1, format, ap);
    perror(buf);
}
