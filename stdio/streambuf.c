#include "unixprog.h"

void print_stdio(const char *name, FILE *fp);
int is_unbuffered(FILE *fp);
int is_linebuffered(FILE *fp);
int buffer_size(FILE *fp);

int main() {
    FILE *fp;
    fputs("Enter any character\n", stdout);
    if (getchar() == EOF) {
        unixprog_sys_error_quit("getchar error");
    }

    fputs("One line to standard error\n", stderr);

    print_stdio("stdin", stdin);
    print_stdio("stdout", stdout);
    print_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL) {
        unixprog_sys_error_quit("fopen error");
    }
    if (getc(fp) == EOF) {
        unixprog_sys_error_quit("getc error");
    }

    print_stdio("/etc/passwd", fp);

    exit(0);
}


void print_stdio(const char *name, FILE *fp) {
    printf("Stream = %s, ", name);
    if (is_unbuffered(fp)) {
        printf("unbuffered");
    } else if (is_linebuffered(fp)) {
        printf("line buffered");
    } else {
        printf("fully buffered");
    }
    printf(", buffer size = %d\n", buffer_size(fp));
}

// For macOS both __SNBF and _IONBF are defined but we need to use fp->_bf.size to get buffer size
// For linux only _IONBF is defined, and the buffer size is given by fp->_IO_buf_end - fp->_IO_buf_base

// macOS
#if defined(__SNBF)

int is_unbuffered(FILE *fp) {
    return fp->_flags & __SNBF;
}

int is_linebuffered(FILE *fp) {
    return fp->_flags & __SLBF;
}

int buffer_size(FILE *fp) {
    return fp->_bf._size;
}

// linux
#elif defined(_IONBF)

int is_unbuffered(FILE *fp) {
    return fp->_flags & _IONBF;
}

int is_linebuffered(FILE *fp) {
    return fp->_flags & _IOLBF;
}

int buffer_size(FILE *fp) {
    return fp->_IO_buf_end - fp->_IO_buf_base;
}

#else

#error Unknown stdio implementation!

#endif
