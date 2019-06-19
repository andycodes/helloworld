#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
pthread_cond_wait() ����������ǰ�̣߳��ȴ�����߳�ʹ��
pthread_cond_signal()��pthread_cond_broadcast����������
pthread_cond_wait() ������pthread_mutex ����ʹ�á�pthread_cond_wait()����һ����wait״̬�ͻ�
�Զ�release mutex���������߳�ͨ��pthread_cond_signal()��pthread_cond_broadcast��
�Ѹ��̻߳��ѣ�ʹpthread_cond_wait()ͨ�������أ�ʱ�����߳����Զ���ø�mutex��
  pthread_cond_signal�����������Ƿ���һ���źŸ�����һ�����ڴ�������
  �ȴ�״̬���߳�,ʹ����������״̬,����ִ��.���û���̴߳�������
  �ȴ�״̬,pthread_cond_signalҲ��ɹ����ء�
  ʹ��pthread_cond_signalһ�㲻���С���Ⱥ���󡱲����������ֻ��һ����
  �̷��źš������ж���߳����������ȴ���������������Ļ���
  ��ô�Ǹ��ݸ��ȴ��߳����ȼ��ĸߵ�ȷ���ĸ��߳̽��յ��źſ�ʼ����ִ��
  ��������߳����ȼ���ͬ������ݵȴ�ʱ��ĳ�����ȷ���ĸ��̻߳���ź�
  �����������һ��pthread_cond_signal������෢��һ�Ρ�
  ����pthread_cond_signal�ڶദ�����Ͽ���ͬʱ���Ѷ���̣߳�����ֻ����һ��
  �̴߳���ĳ������ʱ�����������ѵ��߳̾���Ҫ���� wait�����ҹ淶Ҫ��
  pthread_cond_signal���ٻ���һ��pthread_cond_wait�ϵ��̣߳���ʵ��Щʵ��Ϊ�˼�
  �ڵ���������Ҳ�ỽ�Ѷ���߳�.
   ���⣬ĳЩӦ�ã����̳߳أ�pthread_cond_broadcast����ȫ���̣߳�������ͨ��
   ֻ��Ҫһ�����߳�ȥ��ִ�����������������߳���Ҫ����wait.����ǿ��
   �Ƽ���pthread_cond_wait() ʹ��whileѭ�����������ж�.
*/
pthread_mutex_t mymutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;
void *mythread1(void *param)
{
	printf("begin mythread1.\n");
	pthread_mutex_lock(&mymutex1);
	printf("wait in mythread1.\n");
	pthread_cond_wait(&mycond,&mymutex1);/*������ǰ�߳�*/
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
