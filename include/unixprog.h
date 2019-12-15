#ifndef UNIX_PROGRAMMING_UNIXPROG_H
#define UNIX_PROGRAMMING_UNIXPROG_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLEN 4096  // Max line length
// All functions are prefixed with unixprog
// Functions for error handling
void unixprog_error_return(const char *format, ...);
void unixprog_error_quit(const char *format, ...);
void unixprog_sys_error_quit(const char *format, ...);

#endif //UNIX_PROGRAMMING_UNIXPROG_H
