#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
 
#define __USE_GNU
#include<sched.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>
#define THREAD_MAX_NUM 100  //1��CPU�ڵ���������

#define AFFNITY_CURRENT_TASK 0

int cpu_num = 0;  //cpu�к���


void * threadFun(void *arg)  //arg �����̱߳�ţ��Լ����壩
{
    int i;
    cpu_set_t mask;  //CPU�˵ļ���
    cpu_set_t get;   //��ȡ�ڼ����е�CPU
    int tid = *(int *)arg; 

    printf("this tid is: %d\n", tid);  //��ʾ�ǵڼ����߳�
    
    CPU_ZERO(&mask); //�ÿ�
    CPU_SET(2, &mask); //�����׺���ֵ����������PU2�ϡ�ֱ������1 2 3 4
    if (sched_setaffinity(AFFNITY_CURRENT_TASK, sizeof(mask), &mask))//�����߳�CPU�׺���
    {
        printf("sched_setaffinity eror.\n");
        return;
    }

    CPU_ZERO(&get);
    if (sched_getaffinity(AFFNITY_CURRENT_TASK, sizeof(get), &get))//��ȡ�߳�CPU�׺���
    {
        printf("sched_getaffinity eror.\n");
        return;
    }
    for (i = 0; i < cpu_num; i++)
    {
        if (CPU_ISSET(i, &get))//�ж��߳����ĸ�CPU���׺���
        {
            printf("this thread %d is running on processor: %d\n", tid, i);
        }
    }

    return NULL;
}
 
int main(int argc, char* argv[])
{
    int i;    
    int tid[THREAD_MAX_NUM];
    pthread_t thread[THREAD_MAX_NUM];

    cpu_num = sysconf(_SC_NPROCESSORS_CONF);  //��ȡ����
    printf("system has %i processor(s).\n", cpu_num);

    for(i = 0; i < cpu_num; i++)
    {
        tid[i] = i;  //ÿ���̱߳����и�tid[i]
        pthread_create(&thread[i],NULL,threadFun,(void*)&tid[i]);
    }
    for(i = 0; i < cpu_num; i++)
    {
        pthread_join(thread[i], NULL);//�ȴ����е��߳̽������߳�Ϊ��ѭ������CTRL+C����
    }

    return 0;
}
//gcc cpu_affinity_test.c -lpthread -o affnity_test