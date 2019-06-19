//////////////////////////////////////////////////////////////////////
//	util_buff_pool.h
//////////////////////////////////////////////////////////////////////



#ifndef _UTIL_BUFF_POOL_H_
#define _UTIL_BUFF_POOL_H_

#include "platform.h"


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//C language sector


//////////////////////////////////////////////////////////////////////
//	TCycleBuffer & functions

typedef struct _T_CYCLE_BUFFER_
{
	U8		*buff;
	long	size;
	volatile long	begin;
	volatile long	end;
} TCycleBuffer;

void CBInitialize(TCycleBuffer *pCB, void *buff, long size);
long CBGetUsedLen(const TCycleBuffer *pCB);
long CBGetFreeLen(const TCycleBuffer *pCB);
BOOL CBWriteData(TCycleBuffer *pCB, const void *data, long len);
BOOL CBReadData(TCycleBuffer *pCB, void *data, long len);


//////////////////////////////////////////////////////////////////////
//	TBlockBuffer & functions

typedef struct _T_CYCLE_BUFFER_ TBlockBuffer;

void BBInitialize(TBlockBuffer *pBB, void *buff, long size);
long BBGetUsedLen(const TBlockBuffer *pBB);
long BBGetFreeLen(const TBlockBuffer *pBB);

//functions can only be called by writer
void* BBPreallocBlock(const TBlockBuffer *pBB, long len);
void* BBConformBlock(TBlockBuffer *pBB, void* block, long len);
void* BBAllocBlock(TBlockBuffer *pBB, long len);

//functions can only be called by reader
void BBDeleteBlock(TBlockBuffer *pBB, void *block);
void* BBGetFirstBlock(const TBlockBuffer *pBB);
void* BBGetNextBlock(const TBlockBuffer *pBB, const void *block);
inline long BBGetBlockLen(const void *block);



#ifdef __cplusplus
}

//C++ language sector

#include "plat_thread.h"


//////////////////////////////////////////////////////////////////////
//	class CCycleBuffer

class CCycleBuffer
{
protected:
	TCycleBuffer m_CB;
	BOOL m_bOwnMemory;

	CThreadLock *m_pWriteLock;
	CThreadLock *m_pReadLock;
	CThreadChunkSem *m_pWriteSem;
	CThreadChunkSem *m_pReadSem;

public:
	CCycleBuffer();
	CCycleBuffer(long nSize, void *pBuff = NULL, 
		BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE, 
		BOOL bBlockWrite = FALSE, BOOL bBlockRead = FALSE);
	virtual ~CCycleBuffer();

	BOOL Init(long nSize, void *pBuff = NULL, 
		BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE, 
		BOOL bBlockWrite = FALSE, BOOL bBlockRead = FALSE);
	BOOL Uninit();

	BOOL IsInited();

	long GetUsedLen();
	long GetFreeLen();
	BOOL WriteData(const void *data, long len);
	BOOL ReadData(void *data, long len);
};




//////////////////////////////////////////////////////////////////////
//	class CBlockBuffer

class CBlockBuffer
{
protected:
	TBlockBuffer m_CB;
	BOOL m_bOwnMemory;

	CThreadLock *m_pWriteLock;
	CThreadLock *m_pReadLock;

public:
	CBlockBuffer();
	CBlockBuffer(long nSize, void *pBuff = NULL, 
		BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE);
	virtual ~CBlockBuffer();

	BOOL Init(long nSize, void *pBuff = NULL, 
		BOOL bParellelWrite = FALSE, BOOL bParellelRead = FALSE);
	BOOL Uninit();

	BOOL IsInited();

	long GetUsedLen();
	long GetFreeLen();

	//functions can only be called by writer
	void* PreallocBlock(long len);
	void* ConformBlock(void* block, long len);
	void* AllocBlock(long len);

	//functions can only be called by reader
	void DeleteBlock(void *block);
	void* GetFirstBlock();
	void* GetNextBlock(const void *block);
	inline static long GetBlockLen(const void *block);
};

#endif //__cplusplus

#endif //_UTIL_BUFF_POOL_H_

