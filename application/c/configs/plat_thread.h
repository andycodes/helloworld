////////////////////////////////////////////////////////////////////////////////
//	util_thread.h
//////////////////////////////////////////////////////////////////////



#ifndef _UTIL_THREAD_H_
#define _UTIL_THREAD_H_

#include "../platform.h"

//extern "C" {
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
//}


////////////////////////////////////////////////////////////////////////////////
//	thread classes


typedef void* (*FThreadProc)(void*);

typedef enum E_THREAD_SCHEDULE_POLICY
{
	tspRegular		= SCHED_OTHER,	//no priority
	tspRoundRobin	= SCHED_RR,		//priority between 1 ~ 99, greater means higher priority
	tspFIFO			= SCHED_FIFO	//priority between 1 ~ 99, greater means higher priority
} EThreadSchedPolicy;


class CRawThread
{
protected:
	pthread_t		m_thread;

public:
	CRawThread();
	virtual ~CRawThread();

	BOOL Create(FThreadProc fProc, void *pParam, EThreadSchedPolicy nPolicy = tspRegular, int nPriority = 0);
	BOOL Join(void **ppResult = NULL);
	BOOL Kill(int sig);

	BOOL GetScheduleParam(EThreadSchedPolicy *pnPolicy, int *pnPriority);
};

class CThread : protected CRawThread
{
	static void* ThreadProc(void *pParam);

protected:
	virtual long Running() = 0;
	virtual BOOL Starting() {return TRUE;};
	virtual BOOL Stopping(void *pParam) {return FALSE;};

	CThread();
	virtual ~CThread();

public:
	BOOL Start(EThreadSchedPolicy nPolicy = tspRegular, int nPriority = 0);
	BOOL QueryStop(void *pParam = NULL);
	BOOL Join(long *pnResult = NULL);
};

class CLoopThread : public CThread
{
	U32 m_nLoopInterval;
	U32 m_nLoopCount;

	virtual long Running();
protected:

	virtual BOOL Stopping(void *pParam);

	virtual BOOL Prepare(long *pnResult) {return TRUE;};
	virtual BOOL DoLoop(U32 nLoopCount, long *pnResult) = 0;
	virtual BOOL Cleanup(long *pnResult) {return TRUE;};

	CLoopThread();
	virtual ~CLoopThread();
public:

	BOOL SetLoopInterval(U32 nMS);
	BOOL SetLoopCount(U32 nCount);
};



//	synchronization classes
class CThreadLock
{
	pthread_mutex_t	m_mutex;
public:
	CThreadLock(BOOL bRecursive = FALSE);
	virtual ~CThreadLock();

	BOOL Lock();
	BOOL TryLock();
	BOOL Unlock();
};


class CThreadSem
{
	BOOL		m_bInited;
	BOOL		m_bAtomObtain;
	CThreadLock	m_Lock;
	sem_t		m_sem;

public:
	CThreadSem();
	CThreadSem(int nInitValue, BOOL bAtomObtain = FALSE);
	virtual ~CThreadSem();

	BOOL Init(int nInitValue, BOOL bAtomObtain = FALSE);

	BOOL Obtain(int nCount = 1);
	BOOL Release(int nCount = 1);
	int GetValue();
};

class CThreadRWLock
{
	int			m_nMaxRead;
	CThreadSem	m_Sem;

public:
	CThreadRWLock(int nMaxRead = 5);
	virtual ~CThreadRWLock();

	BOOL SetMaxRead(int nMaxRead);

	BOOL LockRead();
	BOOL UnlockRead();
	BOOL LockWrite();
	BOOL UnlockWrite();
};


class CThreadCondition
{
protected:
	struct TQueryInfo
	{
		BOOL		bResult;
		void 		*pParam;
		CThreadLock	*pLock;
	};
	typedef list<TQueryInfo*> TQueryInfoList;

	TQueryInfoList m_WaitList;

	BOOL		m_bFIFO;
	CThreadLock	m_Lock;

	virtual BOOL DoQuery(void *pParam, BOOL *pbResult) = 0;
	virtual BOOL DoModify(void *pParam) = 0;

	CThreadCondition(BOOL bFIFO = TRUE);
	virtual ~CThreadCondition();

	BOOL SetFIFO(BOOL bFIFO);

public:

	BOOL Query(void *pParam, BOOL bWait = TRUE);
	BOOL Modify(void *pParam);
};

class CThreadChunkSem : protected CThreadCondition
{
protected:
	long m_nValue;

	virtual BOOL DoQuery(void *pParam, BOOL *pbResult);
	virtual BOOL DoModify(void *pParam);

public:
	CThreadChunkSem();
	CThreadChunkSem(long nInitValue, BOOL bFIFO = TRUE);
	virtual ~CThreadChunkSem();

	BOOL Init(long nInitValue, BOOL bFIFO = TRUE);

	BOOL Obtain(long nCount = 1, BOOL bWait = TRUE);
	BOOL Release(long nCount = 1);
	long GetValue();
};



#endif //_UTIL_THREAD_H_

