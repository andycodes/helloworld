#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
pthread_cond_wait() 用于阻塞当前线程，等待别的线程使用
pthread_cond_signal()或pthread_cond_broadcast来唤醒它。
pthread_cond_wait() 必须与pthread_mutex 配套使用。pthread_cond_wait()函数一进入wait状态就会
自动release mutex。当其他线程通过pthread_cond_signal()或pthread_cond_broadcast，
把该线程唤醒，使pthread_cond_wait()通过（返回）时，该线程又自动获得该mutex。
  pthread_cond_signal函数的作用是发送一个信号给另外一个正在处于阻塞
  等待状态的线程,使其脱离阻塞状态,继续执行.如果没有线程处在阻塞
  等待状态,pthread_cond_signal也会成功返回。
  使用pthread_cond_signal一般不会有“惊群现象”产生，他最多只给一个线
  程发信号。假如有多个线程正在阻塞等待着这个条件变量的话，
  那么是根据各等待线程优先级的高低确定哪个线程接收到信号开始继续执行
  。如果各线程优先级相同，则根据等待时间的长短来确定哪个线程获得信号
  。但无论如何一个pthread_cond_signal调用最多发信一次。
  但是pthread_cond_signal在多处理器上可能同时唤醒多个线程，当你只能让一个
  线程处理某个任务时，其它被唤醒的线程就需要继续 wait，而且规范要求
  pthread_cond_signal至少唤醒一个pthread_cond_wait上的线程，其实有些实现为了简单
  在单处理器上也会唤醒多个线程.
   另外，某些应用，如线程池，pthread_cond_broadcast唤醒全部线程，但我们通常
   只需要一部分线程去做执行任务，所以其它的线程需要继续wait.所以强烈
   推荐对pthread_cond_wait() 使用while循环来做条件判断.
*/
pthread_mutex_t mymutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;
void *mythread1(void *param)
{
	printf("begin mythread1.\n");
	pthread_mutex_lock(&mymutex1);
	printf("wait in mythread1.\n");
	pthread_cond_wait(&mycond,&mymutex1);/*阻塞当前线程*/
	pthread_mutex_unlock(&mymutex1);
	printf("end mythread1.\n");
	return NULL;
}
void *mythread2(void *param)
{
	printf("begin mythread2.\n");
	pthread_mutex_lock(&mymutex1);
	printf("wait in mythread2.\n");
	pthread_cond_wait(&mycond,&mymutex1);
	pthread_mutex_unlock(&mymutex1);
	printf("end mythread2.\n");
	return NULL;
}

int main(int argc, char ** argv)
{
	int i;
	int ret = 0;
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,mythread1,NULL);
	pthread_create(&tid2,NULL,mythread2,NULL);
	sleep(2);
	printf("try to wake up mythread1 and mythread2 in main thread.\n");

	switch(atoi(argv[1]))
	{
		case 0:
				ret = pthread_cond_signal(&mycond);
		break;
		case 1:
		default:
				ret = pthread_cond_broadcast(&mycond);
	}


	if(ret){
		printf("error\n");
		return ret;
	}

	void *res;
	pthread_join(tid1, &res);
	pthread_join(tid2, &res);
	printf("end main thread.\n");
	return 0;
}

/* gcc pthread_cond.cpp -lpthread */
