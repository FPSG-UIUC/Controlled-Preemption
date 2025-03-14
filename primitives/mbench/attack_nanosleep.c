#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <asm/param.h>
#include <time.h>

#define CNT_RELOAD_VALUE    10000

long long interval;

int main(int argc, char** argv){
    interval = atoll(argv[1]) - 1;
    // change timerslack to the minimum
    prctl(PR_SET_TIMERSLACK, 1, 0, 0, 0);
    int cnt = CNT_RELOAD_VALUE;
    printf("Attacker PID: %ld\n", (long)getpid());
    sleep(5);
    while(1){
        nanosleep(&(struct timespec){0, interval}, NULL);
        // Attacker dummy workload, to be replaced with the actual attack
        while(cnt) cnt--;
        cnt = CNT_RELOAD_VALUE;
    }
   return 0;
}
