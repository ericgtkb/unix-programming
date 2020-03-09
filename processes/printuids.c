#include "unixprog.h"

int main() {
    printf("Real uid = %d, effective uid = %d\n", getuid(), geteuid());
    exit(0);
}
