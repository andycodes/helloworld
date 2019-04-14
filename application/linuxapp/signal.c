#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>


void sigroutine(int signo)
{
	switch (signo){
	case SIGALRM:
		printf("Catch a signal -- SIGALRM\n");
	break;
	case SIGVTALRM:
		printf("Catch a signal -- SIGVTALRM\n");
	break;
	default:break;
	}
}

int main()
{
	int ret;
	struct itimerval value, ovalue, value2;
	printf("process id is %d\n", getpid());

	signal(SIGALRM, sigroutine);
	value.it_value.tv_sec = 1;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;
	ret = setitimer(ITIMER_REAL, &value, NULL);
	if (ret) {
		printf("setitimer ITIMER_REAL err\n");
		return -1;
	}

	signal(SIGVTALRM, sigroutine);
	value2.it_value.tv_sec = 0;
	value2.it_value.tv_usec = 500000;
	value2.it_interval.tv_sec = 0;
	value2.it_interval.tv_usec = 500000;
	ret = setitimer(ITIMER_VIRTUAL, &value2, NULL);
	if (ret) {
		printf("setitimer ITIMER_VIRTUAL err\n");
		return -2;
	}

	for(;;);
}

