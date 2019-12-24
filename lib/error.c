#include "unixprog.h"
#include <errno.h>
#include <stdarg.h>

// sys_err_flag: whether it's a system error
// error: a copy of errno
static void print_error(int sys_err_flag, int error, const char* format, va_list ap);

// Nonfatal error unrelated to a system call
// Print error message and return
void unixprog_error_return(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_error(0, 0, format, ap);
    va_end(ap);
}

// Fatal error unrelated to a system call
// Print error message and exit
void unixprog_error_quit(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_error(0, 0, format, ap);
    va_end(ap);
    exit(42);
}

// Nonfatal error related to a system call
// Print error message and return
void unixprog_sys_error_return(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_error(1, errno, format, ap);
    va_end(ap);
}

// Fatal error related to a system call
// Print error message and exit
void unixprog_sys_error_quit(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_error(1, errno, format, ap);
    va_end(ap);
    exit(42);
}

// Fatal error related to a system call
// Print error message dump core and exit
void unixprog_sys_error_dump(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_error(1, errno, format, ap);
    va_end(ap);
    abort();  // Dump core and terminate
}

static void print_error(int sys_err_flag, int error, const char* format, va_list ap) {
    char buf[UNIXPROG_MAXLEN];
    vsnprintf(buf, UNIXPROG_MAXLEN - 1, format, ap);  // -1 for '\n'
    // If the error is related to system error add system error message
    if (sys_err_flag) {
        // Append system error message to the string
        snprintf(buf + strlen(buf), UNIXPROG_MAXLEN - strlen(buf) - 1, ": %s", strerror(error));
    }
    strcat(buf, "\n");

    // Make sure that stdout and stderr are in the correct order
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);  // Flushes all stdio output streams
}
