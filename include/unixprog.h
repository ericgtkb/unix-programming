#ifndef UNIX_PROGRAMMING_UNIXPROG_H
#define UNIX_PROGRAMMING_UNIXPROG_H

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// All macros are prefixed with UNIXPROG
#define UNIXPROG_MAXLEN 4096  // Max line length

// Default file access permissions for new files.
#define UNIXPROG_FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// All typedefs are prefixed with unixprog
typedef void unixprog_SigFunc(int);  // signal handlers

// All functions are prefixed with unixprog

// Functions for error handling, lib/error.c
void unixprog_error_return(const char *format, ...);
void unixprog_error_quit(const char *format, ...);
void unixprog_sys_error_return(const char *format, ...);
void unixprog_sys_error_quit(const char *format, ...);
void unixprog_sys_error_dump(const char *format, ...);

// path_alloc function, allocates space for path name depending on platform specifics, lib/pathalloc.c
char *unixprog_path_alloc(size_t *path_size);

// print_exit function, prints a description of the exit status, lib/prexit.c
void unixprog_print_exit(int status);

// print_mask function, prints the names of the signals in the signal mask of the calling process, lib/prmask.c
void unixprog_print_mask(const char *str);

// signal_intr function, prevents any interrupted system calls from being restarted, lib/signalintr.c
unixprog_SigFunc *unixprog_signal_intr(int signo, unixprog_SigFunc *func);

// Functions to synchronize a parent and a child, in lib/tellwait.c
void unixprog_tell_wait();
void unixprog_tell_parent(pid_t pid);
void unixprog_wait_parent();
void unixprog_tell_child(pid_t pid);
void unixprog_wait_child();



#endif //UNIX_PROGRAMMING_UNIXPROG_H
