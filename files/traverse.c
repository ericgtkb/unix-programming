#include "unixprog.h"
#include <dirent.h>
#include <limits.h>

// Define a function type that is use to get information out of a file
typedef int process_func(const char *, const struct stat *, int);

// Use the type to declare the function
static process_func process_file;
static int traverse(char *pathname, process_func *func);
static int do_path(process_func *func);

static long num_reg, num_dir, num_blk, num_chr, num_fifo, num_slink, num_sock, num_tot;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        unixprog_error_quit("Usage: traverse <starting-pathname>");
    }

    int status;
    status = traverse(argv[1], process_file);  // Traverse from the starting pathname and update all the numbers
    num_tot = num_reg + num_dir + num_blk + num_chr + num_fifo + num_slink + num_sock;
    if (num_tot == 0) {
        num_tot = 1;  // Avoiding devide by 0, print 0 for all
    }
    printf("regular files  = %7ld, %5.2f %%\n", num_reg, num_reg * 100.0 / num_tot);
    printf("directories    = %7ld, %5.2f %%\n", num_dir, num_dir * 100.0 / num_tot);
    printf("block special  = %7ld, %5.2f %%\n", num_blk, num_blk * 100.0 / num_tot);
    printf("char special   = %7ld, %5.2f %%\n", num_chr, num_chr * 100.0 / num_tot);
    printf("FIFOs          = %7ld, %5.2f %%\n", num_fifo, num_fifo * 100.0 / num_tot);
    printf("symbolic links = %7ld, %5.2f %%\n", num_slink, num_slink * 100.0 / num_tot);
    printf("sockets        = %7ld, %5.2f %%\n", num_sock, num_sock * 100.0 / num_tot);

    exit(status);
}

#define FTW_F 1  // File other than directory
#define FTW_D 2 // Directory
#define FTW_DNR 3  // Directory that cannot be read
#define FTW_NS 4  // File that we cannot stat

static char *full_path;  // Holds the full pathname for every file
static size_t path_len;


static int process_file(const char *pathname, const struct stat *statptr, int type) {
    switch (type) {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT) {
                case S_IFREG:
                    num_reg++;
                    break;
                case S_IFBLK:
                    num_blk++;
                    break;
                case S_IFCHR:
                    num_chr++;
                    break;
                case S_IFIFO:
                    num_fifo++;
                    break;
                case S_IFLNK:
                    num_slink++;
                    break;
                case S_IFSOCK:
                    num_sock++;
                    break;
                case S_IFDIR:
                    unixprog_sys_error_dump("Fatal error for S_IFDIR for %s", pathname);
            }
            break;
        case FTW_D:
            num_dir++;
            break;
        case FTW_DNR:
            unixprog_sys_error_return("Can't read directory %s", pathname);
            break;
        case FTW_NS:
            unixprog_sys_error_return("stat error for %s", pathname);
            break;
        default:
            unixprog_sys_error_dump("Unknown type %d for pathname %s", type, pathname);
    }
    return 0;
}

// Descend through the hierarchy, starting at pathname, func is called for every file
static int traverse(char *pathname, process_func *func) {
    full_path = unixprog_path_alloc(&path_len);  // Defined in unixprog.h

    if (path_len <= strlen(pathname)) {
        path_len = strlen(pathname) * 2;
        if ((full_path = realloc(full_path, path_len)) == NULL) {
            unixprog_sys_error_quit("realloc failed");
        }
    }
    strcpy(full_path, pathname);
    return do_path(func);
}

static int do_path(process_func *func) {
    struct stat statbuf;
    DIR *dir;
    struct dirent *entry;
    int status, n;

    if (lstat(full_path, &statbuf) < 0) {  // stat error
        return func(full_path, &statbuf, FTW_NS);
    }
    if (!S_ISDIR(statbuf.st_mode)) {  // Not a directory
        return func(full_path, &statbuf, FTW_F);
    }
    // It's a directory. First call func(), then process each filename in the directory.
    if ((status = func(full_path, &statbuf, FTW_D)) != 0) {
        return status;
    }

    n = strlen(full_path);
    if (n + NAME_MAX + 2 > path_len) {  // Expand path buffer
        path_len *= 2;
        if ((full_path = realloc(full_path, path_len)) == NULL) {
            unixprog_sys_error_quit("realloc failed");
        }
    }
    full_path[n++] = '/';
    full_path[n] = 0;

    if ((dir = opendir(full_path)) == NULL) {  // Cannot read directory
        return func(full_path, &statbuf, FTW_DNR);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            // Ignore . and ..
            continue;
        }
        strcpy(&full_path[n], entry->d_name);  // append name after '/'
        if ((status = do_path(func)) != 0) {  // Recursive
            break;
        }
    }
    full_path[n - 1] = 0;  // Erase everything from slash onward

    if (closedir(dir) < 0) {
        unixprog_sys_error_return("Can't close directory %s", full_path);
    }
    return status;
}

