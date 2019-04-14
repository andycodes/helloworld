#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include "platform.h"
#include "plat_thread.h"

CThreadLock g_lock;
long long g_total_count = 0;

class CReadLoop : public CLoopThread
{
public:
	long m_value;

	CReadLoop(long value) {	m_value = value;}

	BOOL DoLoop(U32 nLoopCount, long *pnResult) {
		g_lock.Lock();
		g_total_count += m_value;
		cout<<"READ:"<<m_value<<g_total_count<<endl;   
		g_lock.Unlock();
		OSSleep(100);
		return TRUE;
	}
};

class CWriteLoop : public CLoopThread
{
public:
	long m_value;

	CWriteLoop(long value) {m_value = value;}

	BOOL DoLoop(U32 nLoopCount, long *pnResult) {
		g_lock.Lock();
		g_total_count -= m_value;
		cout<<"WRITE"<<m_value<<g_total_count<<endl;   
		g_lock.Unlock();
		OSSleep(200);
		return TRUE;
	}
};


int main()
{
	CReadLoop read1(1);
	CWriteLoop write1(2);
	read1.Start(tspRoundRobin, 99);
	write1.Start(tspRoundRobin, 1);
	read1.Join(NULL);//Ïß³ÌµÈ´ý
	return 0;
}



