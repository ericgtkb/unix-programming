#include "unixprog.h"

extern char **environ;

int main() {

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    exit(0);
}

// This also works

//int main(int argc, char *argv[], char *envp[]) {
//
//    for (int i = 0; envp[i] != NULL; i++) {
//        printf("%s\n", envp[i]);
//    }
//    exit(0);
//}
