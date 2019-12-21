#include "unixprog.h"

#define BUF_SIZE 48

int main() {
    FILE *fp;
    char buf[BUF_SIZE];

    memset(buf, 'a', BUF_SIZE - 2);
    buf[BUF_SIZE - 2] = '\0';
    buf[BUF_SIZE - 1] = 'X';
    if ((fp = fmemopen(buf, BUF_SIZE, "w+")) == NULL) {
        unixprog_sys_error_quit("fmemopen failed");
    }

    printf("Initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("Before flush: %s\n", buf);
    fflush(fp);
    printf("After flush: %s\n", buf);
    printf("Length of string in buf = %ld\n", (long) strlen(buf));

    memset(buf, 'b', BUF_SIZE - 2);
    buf[BUF_SIZE - 2] = '\0';
    buf[BUF_SIZE - 1] = 'X';
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);
    printf("After fseek: %s\n", buf);
    printf("Length of string in buf = %ld\n", (long) strlen(buf));

    memset(buf, 'c', BUF_SIZE - 2);
    buf[BUF_SIZE - 2] = '\0';
    buf[BUF_SIZE - 1] = 'X';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("After fclose: %s\n", buf);
    printf("Length of string in buf = %ld\n", (long) strlen(buf));

    exit(0);
}
