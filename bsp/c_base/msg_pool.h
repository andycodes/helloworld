//msg_pool.h:
//
//////////////////////////////////////////////////////////////////////


#ifndef _MSG_POOL_H_
#define _MSG_POOL_H_

#include "platform.h"
#include "util_buff_pool.h"



#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//////////////////////////////////////////////////////////////////////
//	structure of Raw Message
/*message type:应用开发人员定义的消息类型应在0到0x7FFFFFFF之间
* U8	_param[]; 0长数组不占有空间
* sizeof(TRawMsg)=12
*/

#pragma pack(1)
typedef struct _T_RAW_MSG_
{
	long __spare;
	U32	type;		
	I32	len;			//parameter length, <= 0 for no parameter
	U8	_param[];	//buffer of parameter
} TRawMsg;
#pragma pack()

#define INIT_MSG_HEADER(msg) if (0); else {(msg)->__spare=1;(msg)->type=0;(msg)->len=sizeof(*(msg))-sizeof(TRawMsg);}

#define MSG_SPARE_LEN (sizeof(long))

#define MSG_HEADER(msg) (((U8*)(msg))+MSG_SPARE_LEN)
#define MSG_HEADER_LEN (sizeof(TRawMsg)-MSG_SPARE_LEN)

#define MSG_PARAM(msg) ((U8*)((msg)->_param))
#define MSG_PARAM_LEN(msg) (((msg)->len>0)?(msg)->len:0)

#define MSG_DATA(msg) MSG_HEADER(msg)
#define MSG_DATA_LEN(msg) (MSG_PARAM_LEN(msg)+MSG_HEADER_LEN)

#define MSG_TOTAL_LEN(msg) (MSG_PARAM_LEN(msg)+sizeof(TRawMsg))

TRawMsg* AssembleMsg(void* buffer, int buffer_size, U32 type, I32 len, const void *param);

#ifdef __cplusplus
}

//////////////////////////////////////////////////////////////////////
//	interfaces


struct IMsgPool
{
	virtual BOOL ReadMsg(TRawMsg *msg, I32 buff_size) = 0;
	virtual BOOL WriteMsg(TRawMsg *msg) = 0;
	virtual ~IMsgPool();
};



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolBuffer


class CMsgPoolBuffer : public CCycleBuffer, public IMsgPool
{
public:
	CMsgPoolBuffer();
	virtual ~CMsgPoolBuffer();

	BOOL Init(long nSize, void *pBuff = NULL, 
		BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE);

	BOOL ReadMsg(TRawMsg *msg, I32 buff_size);
	BOOL WriteMsg(TRawMsg *msg);
};



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolFile

class CMsgPoolFile : public IMsgPool
{
	TOSFileHandle m_fileIn, m_fileOut;
	CThreadLock *m_pWriteLock;
	CThreadLock *m_pReadLock;

public:
	CMsgPoolFile();
	virtual ~CMsgPoolFile();

	BOOL Init(TOSFileHandle fileIn, TOSFileHandle fileOut, 
		BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE);
	BOOL Uninit();
	BOOL IsInited();

	BOOL ReadMsg(TRawMsg *msg, I32 buff_size);
	BOOL WriteMsg(TRawMsg *msg);
};



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolPipe

class CMsgPoolPipe : public CMsgPoolFile
{
public:
	BOOL Init(BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE);
};



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolUnix

class CMsgPoolUnix : public IMsgPool
{
	TOSFileHandle m_fileIn, m_fileOut;

public:
	CMsgPoolUnix();
	virtual ~CMsgPoolUnix();

	BOOL Init();
	BOOL Init(TOSFileHandle fileIn, TOSFileHandle fileOut);
	BOOL Uninit();
	BOOL IsInited();

	BOOL ReadMsg(TRawMsg *msg, I32 buff_size);
	BOOL WriteMsg(TRawMsg *msg);
};



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolQueue

class CMsgPoolQueue : public IMsgPool
{
	int m_nQueueID;

public:
	CMsgPoolQueue();
	virtual ~CMsgPoolQueue();

	BOOL Init();
	BOOL Uninit();
	BOOL IsInited();

	BOOL ReadMsg(TRawMsg *msg, I32 buff_size);
	BOOL WriteMsg(TRawMsg *msg);
};



#endif //__cplusplus


#endif //_MSG_POOL_H_


