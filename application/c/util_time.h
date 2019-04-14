////////////////////////////////////////////////////////////////////////////////
//	util_time.h
//////////////////////////////////////////////////////////////////////



#ifndef  _UTIL_TIME_H_
#define _UTIL_TIME_H_

#include "platform.h"
#include "msg_pool.h"
#include "util_thread.h"


////////////////////////////////////////////////////////////////////////////////
//	utility functions

struct TUTime
{
	int year;			/* year */
	int month;			/* month */
	int day;			/* day of the month */
	int hour;			/* hours */
	int minute;			/* minutes */
	int second;			/* seconds */
	int microsecond;	/*microseconds*/
	int dayofweek;		/* day of the week */
	int dayofyear;		/* day in the year */
};

I64 TUGetTime();
void TUGetTime(TUTime &time);

I64 TUConvertTime(const TUTime &time);
void TUConvertTime(TUTime &time, I64 value);


////////////////////////////////////////////////////////////////////////////////
//	class CStopwatch

class CStopwatch
{
protected:
	int	m_nStopCount;
	I64	m_nTotalTime;
	I64	m_nLastTime;

public:
	CStopwatch();
	virtual ~CStopwatch();
	void Reinit();

	void Start();
	void Stop(I64 *interval = NULL);

	int GetStopCount();
	I64 GetTotalTime();
	I64 GetAverageInterval();
};


////////////////////////////////////////////////////////////////////////////////
//	class CTimer

class CRawTimer;
class CTimerManager;

typedef multimap<I64, CRawTimer*> CTimerMap;

class CRawTimer
{
protected:
	friend class CTimerManager;

	CTimerManager		*m_pMngr;
	CTimerMap::iterator	m_it;

	U32					m_msExpire;
	BOOL				m_bPeriodic;

	virtual void OnTimer() = 0;

	CRawTimer();
	virtual ~CRawTimer();
public:;

	BOOL SetTime(U32 msExpire, BOOL bPeriodic = FALSE);
};



////////////////////////////////////////////////////////////////////////////////
//	class CTimerManager

class CTimerManager
{
protected:
	CThreadLock *m_pLock;
	CTimerMap m_TimerMap;

	virtual BOOL CheckTimer();

public:
	CTimerManager(BOOL bNeedLock = TRUE);
	virtual ~CTimerManager();

	virtual BOOL AddTimer(CRawTimer *pTimer);
	virtual BOOL KillTimer(CRawTimer *pTimer);
};



////////////////////////////////////////////////////////////////////////////////
//	class CCallbackTimer

class CCallbackTimer;
typedef void (*FTimerCallback)(CCallbackTimer *pTimer, void *pParam);

class CCallbackTimer : public CRawTimer
{
protected:
	FTimerCallback m_fFun;
	void *m_pParam;

	virtual void OnTimer();

public:
	CCallbackTimer();
	virtual ~CCallbackTimer();

	BOOL SetCallback(FTimerCallback fFun, void *pParam);
};



////////////////////////////////////////////////////////////////////////////////
//	class CMsgTimer

class IMsg;

class CMsgTimer : public CRawTimer
{
protected:
	IMsg *m_pTarget;
	U8 *m_pMsg;

	virtual void OnTimer();

public:
	CMsgTimer();
	virtual ~CMsgTimer();

	BOOL SetMessage(IMsg *tgt, TRawMsg *msg);
};


////////////////////////////////////////////////////////////////////////////////
//	class CTimerThread

class CTimerThread : public CLoopThread, public CTimerManager
{
protected:
	virtual BOOL DoLoop(U32 nLoopCount, long *pnResult);

public:
	CTimerThread(U32 msPrecision = 0);
	virtual ~CTimerThread();

	BOOL SetPrecision(U32 msPrecision);
};


CTimerThread* TUGetDefaultTimerThread();


#endif //_UTIL_TIME_H_

