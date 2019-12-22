#include "unixprog.h"
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2();

static jmp_buf jump_buffer;
static int global_val;

int main() {
    int auto_val;
    register int register_val;
    volatile int volatile_val;
    static int static_val;

    global_val = 1;
    auto_val = 2;
    register_val = 3;
    volatile_val = 4;
    static_val=5;

    if (setjmp(jump_buffer) != 0) {
        printf("After longjmp:\n");
        printf("global_val = %d, auto_val = %d, register_val = %d, volatile_val = %d, static_val = %d\n",
               global_val, auto_val, register_val, volatile_val, static_val);
        exit(0);
    }

    // Change varibales after setjmp, but before longjmp
    global_val = 95;
    auto_val = 96;
    register_val = 97;
    volatile_val = 98;
    static_val = 99;

    f1(auto_val, register_val, volatile_val, static_val);  // Never returns

    exit(0);
}

static void f1(int i, int j, int k, int l) {
    printf("in f1():\n");
    printf("global_val = %d, auto_val = %d, register_val = %d, volatile_val = %d, static_val = %d\n",
           global_val, i, j, k, l);
    f2();

}

static void f2() {
    longjmp(jump_buffer, 1);
}

