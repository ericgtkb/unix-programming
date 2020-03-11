#include "unixprog.h"
#include <sys/times.h>

static void print_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    for (int i = 1; i < argc; i++) {
        do_cmd(argv[i]);
    }
    exit(0);
}

static void do_cmd(char *cmd) {
    struct tms tmsstart;
    struct tms tmsend;
    clock_t start;
    clock_t end;
    int status;

    printf("\nCommand: %s\n", cmd);

    if ((start = times(&tmsstart)) == -1) {
        unixprog_sys_error_quit("times error");
    }

    if ((status = system(cmd)) < 0) {
        unixprog_sys_error_quit("system() error");
    }

    if ((end = times(&tmsend)) == -1) {
        unixprog_sys_error_quit("times error");
    }

    print_times(end - start, &tmsstart, &tmsend);
    unixprog_print_exit(status);
}

static void print_times(clock_t real, struct tms *tmsstart, struct tms *tmsend) {
    static long clktck = 0;
    if (clktck == 0) {  // Fetch clock ticks per second first time
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
            unixprog_sys_error_quit("sysconf error");
        }
    }
    printf("  real:  %7.2f\n", real / (double) clktck);
    printf("  user:  %7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf("  sys:  %7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
    printf("  child user:  %7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf("  child sys:  %7.2f\n", (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);

}
