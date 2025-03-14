#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#include <sys/types.h>
#include <sys/wait.h>

// The code is loosely based on the demo on the timer_create() man page of the
// Linux man-mages project. 2015-07-23.
// (C) 2017, Bernd Porr, mail@berndporr.me.uk
// License is GPL-3.0. See the LICENSE file.

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN
#define CNT_RELOAD_VALUE    10000

// global variable to check if the callback is called
// from our timer
timer_t timerid;

int count = CNT_RELOAD_VALUE;

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE);	\
	} while (0)


int entry = 0;
static void handler(int sig, siginfo_t *si, void *uc){
	while(count) --count;
	count = CNT_RELOAD_VALUE;
}


int main(int argc, char *argv[]){
	printf("Attacker PID: %d\n", getpid());
	long long interval = atoll(argv[1]);
	printf("%lld\n", interval);
	struct sigevent sev;
	struct itimerspec its;
	long long freq_nanosecs;
	sigset_t mask;
	siginfo_t info;
	struct sigaction sa;

	// printf("%ld\n", (long)gettid());
   	printf("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIG, &sa, NULL) == -1)
		errExit("sigaction");
	sigemptyset(&mask);
	sigaddset(&mask, SIG);
	
	/* Create the timer */
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = &timerid;
	if (timer_create(CLOCKID, &sev, &timerid) == -1)
		errExit("timer_create");

	printf("timer ID is 0x%lx\n", (long) timerid);

	int pid = fork();
	if(pid == 0){
		pause();
	}

	/* Start the timer */

	// starts instantly
	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = 1;

	// and fires every interval
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = interval;
	if (timer_settime(timerid, 0, &its, NULL) == -1)
        errExit("timer_settime");

	// pause main thread and let interrupt handler wake it up		
	while(1) pause();

	exit(EXIT_SUCCESS);
}
