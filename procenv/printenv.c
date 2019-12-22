#include "unixprog.h"

int main() {
    for (int i = 0; __environ[i] != NULL; i++) {
        printf("%s\n", __environ[i]);
    }
    exit(0);
}
