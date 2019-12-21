#include "unixprog.h"

int main() {
    char name[L_tmpnam];
    char line[UNIXPROG_MAXLEN];
    FILE *fp;

    // tmpnam is not safe!
    printf("%s\n", tmpnam(NULL));  // First temp name

    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) {
        unixprog_sys_error_quit("tmpfile error");
    }
    fputs("One line of output\n", fp);
    rewind(fp);

    if (fgets(line, sizeof(line), fp) == NULL) {
        unixprog_sys_error_quit("fgets error");
    }
    fputs(line, stdout);

    exit(0);
}
