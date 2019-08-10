//////////////////////////////////////////////////////////////////////
//	util_thread.cpp
//////////////////////////////////////////////////////////////////////


#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include "../configs/plat_thread.h"


////////////////////////////////////////////////////////////////////////////////
//	class CRawThread

CRawThread::CRawThread()
{
	m_thread = 0;
}

CRawThread::~CRawThread()
{
}

BOOL CRawThread::Create(FThreadProc fProc, void *pParam, 
		EThreadSchedPolicy nPolicy/*=tspRegular*/, int nPriority/*=0*/)
{
	pthread_attr_t attr;
	struct sched_param param;

	if (m_thread != 0)
		return FALSE;

	pthread_attr_init(&attr);
	//设置线程调度策略
	pthread_attr_setschedpolicy(&attr, nPolicy);
	pthread_attr_getschedparam(&attr, &param);
	param.__sched_priority = nPriority;//调度优先级
	pthread_attr_setschedparam(&attr, &param);

	if (0 == pthread_create(&m_thread, NULL, fProc, pParam))//fProc  线程函数
	{
	    return TRUE;
    }
    
	return FALSE;
}

BOOL CRawThread::Join(void **ppResult/*=NULL*/)
{
	if (m_thread == 0)
    {
	    return FALSE;
    }

    /*pthread_join 父进程阻塞等待子线程推出
    父进程捕获到子线程退出信号后，父进程退出，否则父进程阻塞状态*/
	if (0 == pthread_join(m_thread, ppResult))
	{
		m_thread = 0;
		return TRUE;
	}
    
	return FALSE;
}

BOOL CRawThread::Kill(int sig)//发送信号
{
	if (m_thread == 0)
		return FALSE;
	return (0== pthread_kill(m_thread, sig));
}

BOOL CRawThread::GetScheduleParam(EThreadSchedPolicy *pnPolicy, int *pnPriority)
{
	if (m_thread == 0)
		return FALSE;

	struct sched_param param;
	int nPolicy;
	if (0 == pthread_getschedparam(m_thread, &nPolicy, &param))
	{
		if (pnPolicy)
			*pnPolicy = (EThreadSchedPolicy)nPolicy;
		if (pnPriority)
			*pnPriority = param.__sched_priority;
		return TRUE;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//	class CThread

void* CThread::ThreadProc(void *pParam)
{
	return (void*)((CThread*)pParam)->Running();
}

CThread::CThread()
{
}

CThread::~CThread()
{
}

BOOL CThread::Start(EThreadSchedPolicy nPolicy/*=tspRegular*/, int nPriority/*=0*/)
{
	if (! Starting())
    {
	    return FALSE;
    }
    
	return Create((FThreadProc)ThreadProc, (void*)this, nPolicy, nPriority);
}

BOOL CThread::QueryStop(void *pParam/*=NULL*/)
{
	return Stopping(pParam);
}

BOOL CThread::Join(long *pnResult/*=NULL*/)
{
	return CRawThread::Join((void**)pnResult);
}


////////////////////////////////////////////////////////////////////////////////
//	class CLoopThread

long CLoopThread::Running()
{
	long nResult = 0;
	U32 nCount = 0;

	if (! Prepare(&nResult))
		return nResult;

	while ((m_nLoopCount != (U32)-1) && ((m_nLoopCount == 0) || (nCount < m_nLoopCount))) {
		if ((m_nLoopInterval > 0) && (nCount > 0))
			OSSleep(m_nLoopInterval);

		if (! DoLoop(nCount, &nResult))
			break;

		nCount ++;
	}

	Cleanup(&nResult);
	return nResult;
}

BOOL CLoopThread::Stopping(void *pParam)
{
	m_nLoopCount = (U32)-1;
	return TRUE;
}

CLoopThread::CLoopThread()
{
	m_nLoopCount = 0;
	m_nLoopInterval = 0;
}

CLoopThread::~CLoopThread()
{
}

BOOL CLoopThread::SetLoopInterval(U32 nMS)
{
	m_nLoopInterval = nMS;
}

BOOL CLoopThread::SetLoopCount(U32 nCount)
{
	m_nLoopCount = nCount;
}


////////////////////////////////////////////////////////////////////////////////
//	class CThreadLock

/*mutex init*/

/*
PTHREAD_MUTEX_RECURSIVE_NP
嵌套锁，允许同一个线程对同一个锁成功获得多次，
并通过多次unlock解锁。如果是不同线程请求，
则在加锁线程解锁时重新竞争

PTHREAD_MUTEX_FAST_NP  普通锁*/
CThreadLock::CThreadLock(BOOL bRecursive/*=FALSE*/)
{
	pthread_mutexattr_t mutex_attr;
	pthread_mutexattr_init(&mutex_attr);
	if (bRecursive) {
		pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE_NP);
	} else {
		pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_FAST_NP);
	}

	pthread_mutex_init(&m_mutex, &mutex_attr);
	pthread_mutexattr_destroy(&mutex_attr);
}

CThreadLock::~CThreadLock()
{
	pthread_mutex_destroy(&m_mutex);
}

/*解锁者可以是同进程内任何线程*/
BOOL CThreadLock::Lock()
{
	return (0 == pthread_mutex_lock(&m_mutex));
}

/*必须由加锁者解锁才有效*/
BOOL CThreadLock::TryLock()
{
	return (0 == pthread_mutex_trylock(&m_mutex));
}

BOOL CThreadLock::Unlock()
{
	return (0 == pthread_mutex_unlock(&m_mutex));
}



//	class CThreadSem
CThreadSem::CThreadSem()
{
	m_bInited = FALSE;
}

CThreadSem::CThreadSem(int nInitValue, BOOL bAtomObtain/*=FALSE*/)
{
	Init(nInitValue, bAtomObtain);
}

CThreadSem::~CThreadSem()
{
	if (m_bInited)
		sem_destroy(&m_sem);
}

BOOL CThreadSem::Init(int nInitValue, BOOL bAtomObtain/*=FALSE*/)
{
	m_bAtomObtain = bAtomObtain;
	sem_init(&m_sem, 0, nInitValue);//0---进程内共享
	m_bInited = TRUE;
	return TRUE;
}

BOOL CThreadSem::Obtain(int nCount/*=1*/)
{
	if (m_bAtomObtain)
		m_Lock.Lock();

	for (; nCount > 0; nCount --)
		sem_wait(&m_sem);

	if (m_bAtomObtain)
		m_Lock.Unlock();

	return TRUE;
}

BOOL CThreadSem::Release(int nCount/*=1*/)
{
	for (; nCount > 0; nCount --)
		sem_post(&m_sem);
}

int CThreadSem::GetValue()
{
	int value = 0;
	sem_getvalue(&m_sem, &value);
	return value;
}


////////////////////////////////////////////////////////////////////////////////
//	class CThreadRWLock

CThreadRWLock::CThreadRWLock(int nMaxRead/*=5*/)
{
	m_nMaxRead = nMaxRead;
	m_Sem.Init(m_nMaxRead, TRUE);
}

CThreadRWLock::~CThreadRWLock()
{
}

BOOL CThreadRWLock::SetMaxRead(int nMaxRead)
{
	int nDelta = nMaxRead - m_nMaxRead;
	if (nDelta >0)
		m_Sem.Release(nDelta);
	else if (nDelta < 0)
		m_Sem.Obtain(- nDelta);

	m_nMaxRead = nMaxRead;
	return TRUE;
}

BOOL CThreadRWLock::LockRead()
{
	return m_Sem.Obtain(1);
}

BOOL CThreadRWLock::UnlockRead()
{
	return m_Sem.Release(1);
}

BOOL CThreadRWLock::LockWrite()
{
	return m_Sem.Obtain(m_nMaxRead);
}

BOOL CThreadRWLock::UnlockWrite()
{
	return m_Sem.Release(m_nMaxRead);
}



////////////////////////////////////////////////////////////////////////////////
//	class CThreadCondition
/*
上面的例子展示了冒号的这个用法，下面对这个用法进行几点说明：
1)初始化列表的作用相当于在构造函数内进行相应成员变量的赋值，但两者是有差别的。
在初始化列表中是对变量进行初始化，而在构造函数内是进行赋值操作。两都的差别在对于像const类型数据的操作上表现得尤为明显。我们知道，const类型的变量必须在定义时进行初始化，而不能对const型的变量进行赋值，因此const类型的成员变量只能（而且必须）在初始化列表中进行初始化，即下面的代码将会出错：
*/
CThreadCondition::CThreadCondition(BOOL bFIFO/*=TRUE*/)
	: m_Lock(TRUE)
{
	m_bFIFO = bFIFO;
}

CThreadCondition::~CThreadCondition()
{
	while (m_WaitList.size() > 0) {
		TQueryInfo *pInfo = m_WaitList.front();
		pInfo->bResult = FALSE;
		pInfo->pLock->Unlock();
		m_WaitList.pop_front();
	}
}

BOOL CThreadCondition::SetFIFO(BOOL bFIFO)
{
	m_bFIFO = bFIFO;
	return TRUE;
}

BOOL CThreadCondition::Query(void *pParam, BOOL bWait/*=TRUE*/)
{
	BOOL bResult = FALSE;
	BOOL bSuccess = FALSE;
	TQueryInfo WaitInfo;
	CThreadLock WaitLock(FALSE);

	m_Lock.Lock();

	if (! (m_bFIFO && (m_WaitList.size() > 0)))
		bSuccess = DoQuery(pParam, &bResult);

	if ((! bSuccess) && bWait)
	{
		WaitLock.Lock();
		WaitInfo.bResult = FALSE;
		WaitInfo.pParam = pParam;
		WaitInfo.pLock = &WaitLock;

		m_WaitList.push_back(&WaitInfo);/*Add element at the end*/
	}

	m_Lock.Unlock();

	if ((! bSuccess) && bWait)
	{
		WaitLock.Lock();
		bResult = WaitInfo.bResult;
	}

	return bResult;
}

BOOL CThreadCondition::Modify(void *pParam)
{
	m_Lock.Lock();

	BOOL bResult = DoModify(pParam);
	if (bResult)
	{
		TQueryInfo *pInfo;
		TQueryInfoList::iterator it = m_WaitList.begin();
		while (it != m_WaitList.end())
		{
			pInfo = *it;

			if (DoQuery(pInfo->pParam, &pInfo->bResult))
			{
				pInfo->pLock->Unlock();

				TQueryInfoList::iterator it_tmp = it;
				it ++;
				m_WaitList.erase(it_tmp);
			}
			else if (m_bFIFO)
			{
				break;
			}
			else
			{
				it ++;
			}

		}
	}

	m_Lock.Unlock();
	return bResult;
}




////////////////////////////////////////////////////////////////////////////////
//	class CThreadChunkSem

CThreadChunkSem::CThreadChunkSem()
{
	m_nValue = 0;
}

CThreadChunkSem::CThreadChunkSem(long nInitValue, BOOL bFIFO/*=TRUE*/)
{
	Init(nInitValue, bFIFO);
}

CThreadChunkSem::~CThreadChunkSem()
{
}


BOOL CThreadChunkSem::DoQuery(void *pParam, BOOL *pbResult)
{
	if (m_nValue >= ((long)pParam))
	{
		m_nValue -= (long)pParam;
		*pbResult = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CThreadChunkSem::DoModify(void *pParam)
{
	m_nValue += (long)pParam;
}

BOOL CThreadChunkSem::Init(long nInitValue, BOOL bFIFO/*=TRUE*/)
{
	m_nValue = nInitValue;
	SetFIFO(bFIFO);
}

BOOL CThreadChunkSem::Obtain(long nCount/*=1*/, BOOL bWait/*=TRUE*/)
{
	return Query((void*)nCount, bWait);
}

BOOL CThreadChunkSem::Release(long nCount/*=1*/)
{
	return Modify((void*)nCount);
}

long CThreadChunkSem::GetValue()
{
	return m_nValue;
}




