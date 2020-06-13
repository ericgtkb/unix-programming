#include "unixprog.h"

unsigned int sleep1(unsigned int seconds);

int main() {
    printf("Using the problematic sleep1 function from sleep1.c...\n");
    sleep1(3);
    exit(0);
}
