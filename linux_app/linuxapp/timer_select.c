#include <pthread.h>
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h>

/*seconds: the seconds; mseconds: the micro seconds*/
void setTimer(int seconds, int mseconds)
{
    struct timeval temp;
    time_t timer;//time_t就是long int 类型
    struct tm *tblock;

    temp.tv_sec = seconds;
    temp.tv_usec = mseconds;

    select(0, NULL, NULL, NULL, &temp);

    timer = time(NULL);
    tblock = localtime(&timer);
    printf("Local time is: %s\n", asctime(tblock));

    return ;
}

void *timer_select(void *param)
{
	for(;;)
	{
		 setTimer(1, 0);
	}

	return NULL;
}

int main()
{
	int i;
	pthread_t tid1;

	pthread_create(&tid1,NULL,timer_select,NULL);

	void *res;
	pthread_join(tid1, &res);

    return 0;
}



