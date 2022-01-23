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
#define THREAD_MAX_NUM 100  //1个CPU内的最多进程数

#define AFFNITY_CURRENT_TASK 0

int cpu_num = 0;  //cpu中核数


void * threadFun(void *arg)  //arg 传递线程标号（自己定义）
{
    int i;
    cpu_set_t mask;  //CPU核的集合
    cpu_set_t get;   //获取在集合中的CPU
    int tid = *(int *)arg; 

    printf("this tid is: %d\n", tid);  //显示是第几个线程
    
    CPU_ZERO(&mask); //置空
    CPU_SET(2, &mask); //设置亲和力值，都设置在PU2上。直接设置1 2 3 4
    if (sched_setaffinity(AFFNITY_CURRENT_TASK, sizeof(mask), &mask))//设置线程CPU亲和力
    {
        printf("sched_setaffinity eror.\n");
        return;
    }

    CPU_ZERO(&get);
    if (sched_getaffinity(AFFNITY_CURRENT_TASK, sizeof(get), &get))//获取线程CPU亲和力
    {
        printf("sched_getaffinity eror.\n");
        return;
    }
    for (i = 0; i < cpu_num; i++)
    {
        if (CPU_ISSET(i, &get))//判断线程与哪个CPU有亲和力
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

    cpu_num = sysconf(_SC_NPROCESSORS_CONF);  //获取核数
    printf("system has %i processor(s).\n", cpu_num);

    for(i = 0; i < cpu_num; i++)
    {
        tid[i] = i;  //每个线程必须有个tid[i]
        pthread_create(&thread[i],NULL,threadFun,(void*)&tid[i]);
    }
    for(i = 0; i < cpu_num; i++)
    {
        pthread_join(thread[i], NULL);//等待所有的线程结束，线程为死循环所以CTRL+C结束
    }

    return 0;
}
//gcc cpu_affinity_test.c -lpthread -o affnity_test