//////////////////////////////////////////////////////////////////////
//	util_buff_pool.cpp
//////////////////////////////////////////////////////////////////////


#include "util_buff_pool.h"


//////////////////////////////////////////////////////////////////////
//	TCycleBuffer & functions


void CBInitialize(TCycleBuffer *pCB, void *buff, long size)
{
	memset(pCB, 0, sizeof(TCycleBuffer));
	pCB->buff = (U8*)buff;
	pCB->size = size;
}

long CBGetUsedLen(const TCycleBuffer *pCB)
{
	long l = pCB->end - pCB->begin;
	return (l >=0) ? l : (pCB->size + l);
}

long CBGetFreeLen(const TCycleBuffer *pCB)
{
	long l = pCB->begin - pCB->end;
	return (l > 0) ? (l - 1) : (pCB->size + l - 1);
}

BOOL CBWriteData(TCycleBuffer *pCB, const void *data, long len)
{
	long b = pCB->begin;/*read*/
	long e = pCB->end;/*write*/
	long s = pCB->size;
	long l1, l2;

	if (b > e)
	{
		l1 = b - e - 1;
		l2 = 0;
	}
	else
	{
		l1 = s - e;
		l2 = b - 1;
	}

	if ((l1 + l2) < len)
		return FALSE;

	if (l1 > len)
		l1 = len;
	l2 = len - l1;

	if (l1 > 0)
		memcpy(pCB->buff + e, data, l1);
	if (l2 > 0)
		memcpy(pCB->buff, ((U8*)data) + l1, l2);

	pCB->end = (e + len) % s;

	return TRUE;
}

BOOL CBReadData(TCycleBuffer *pCB, void *data, long len)
{
	long b = pCB->begin;
	long e = pCB->end;
	long s = pCB->size;
	long l1, l2;

	if (e >= b)
	{
		l1 = e - b;
		l2 = 0;
	}
	else
	{
		l1 = s - b;
		l2 = e;
	}

	if ((l1 + l2) < len)
		return FALSE;

	if (l1 > len)
		l1 = len;
	l2 = len - l1;

	if ((l1 > 0) && data)
		memcpy(data, pCB->buff + b, l1);
	if ((l2 > 0) && data)
		memcpy(((U8*)data) + l1, pCB->buff, l2);

	pCB->begin= (b + len) % s;

	return TRUE;
}




//////////////////////////////////////////////////////////////////////
//	class CCycleBuffer

CCycleBuffer::CCycleBuffer()
{
	memset(&m_CB, 0, sizeof(m_CB));
	m_bOwnMemory = FALSE;
	m_pWriteLock = NULL;
	m_pReadLock = NULL;
	m_pWriteSem = NULL;
	m_pReadSem = NULL;
}

CCycleBuffer::CCycleBuffer(long nSize, void *pBuff/*=NULL*/, 
	BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/, 
	BOOL bBlockWrite/*=FALSE*/, BOOL bBlockRead/*=FALSE*/)
{
	Init(nSize, pBuff, bParellelWrite, bParellelRead, bBlockWrite, bBlockRead);
}

CCycleBuffer::~CCycleBuffer()
{
	Uninit();
}

BOOL CCycleBuffer::Init(long nSize, void *pBuff/*=NULL*/, 
	BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/, 
	BOOL bBlockWrite/*=FALSE*/, BOOL bBlockRead/*=FALSE*/)
{
	memset(&m_CB, 0, sizeof(m_CB));
	if (pBuff)
	{
		m_CB.buff = (U8*)pBuff;
		m_bOwnMemory = FALSE;
	}
	else
	{
		m_CB.buff = new U8 [nSize];
		m_bOwnMemory = TRUE;
	}
	m_CB.size = nSize;

	if (bParellelWrite)
		m_pWriteLock = new CThreadLock (TRUE);
	if (bParellelRead)
		m_pReadLock = new CThreadLock (TRUE);
	if (bBlockWrite)
		m_pWriteSem = new CThreadChunkSem(nSize - 1);
	if (bBlockRead)
		m_pReadSem = new CThreadChunkSem(0);

	return TRUE;
}

BOOL CCycleBuffer::Uninit()
{
	if (m_bOwnMemory && m_CB.buff)
		delete [] m_CB.buff;
	memset(&m_CB, 0, sizeof(m_CB));
	m_bOwnMemory = FALSE;

	if (m_pWriteLock)
		delete m_pWriteLock;
	m_pWriteLock = NULL;

	if (m_pReadLock)
		delete m_pReadLock;
	m_pReadLock = NULL;

	if (m_pWriteSem)
		delete m_pWriteSem;
	m_pWriteSem = NULL;

	if (m_pReadSem)
		delete m_pReadSem;
	m_pReadSem = NULL;

	return TRUE;
}

BOOL CCycleBuffer::IsInited()
{
	return (m_CB.buff != NULL);
}

long CCycleBuffer::GetUsedLen()
{
	return CBGetUsedLen(&m_CB);
}

long CCycleBuffer::GetFreeLen()
{
	return CBGetFreeLen(&m_CB);
}

BOOL CCycleBuffer::WriteData(const void *data, long len)
{
	if (m_pWriteLock)
		m_pWriteLock->Lock();

	if (m_pWriteSem)
		m_pWriteSem->Obtain(len);

	BOOL bResult = CBWriteData(&m_CB, data, len);

	if (bResult && m_pReadSem)
		m_pReadSem->Release(len);

	if (m_pWriteLock)
		m_pWriteLock->Unlock();
	return bResult;
}

BOOL CCycleBuffer::ReadData(void *data, long len)
{
	if (m_pReadLock)
		m_pReadLock->Lock();

	if (m_pReadSem)
		m_pReadSem->Obtain(len);

	BOOL bResult = CBReadData(&m_CB, data, len);

	if (bResult && m_pWriteSem)
		m_pWriteSem->Release(len);

	if (m_pReadLock)
		m_pReadLock->Unlock();
	return bResult;
}




//////////////////////////////////////////////////////////////////////
//	TBlockBuffer & functions


#pragma pack(1)

typedef struct _T_BUFFER_BLOCK_
{
	U32	length	: 31;
	U32	removed	: 1;
	U8	data[];
} TBufferBlock;

#pragma pack()

#define BB_BLOCK_DATA_OFFSET ((long)(((TBufferBlock*)0)->data))
#define BB_GET_BLOCK_DATA(header) ((void*)((header)->data))
#define BB_GET_BLOCK_HEADER(data) ((TBufferBlock*)(((U8*)(data))-BB_BLOCK_DATA_OFFSET))
#define BB_GET_BLOCK_OFFSET(bb, pointer) ((long)(((U8*)(pointer)) - (bb)->buff))
#define BB_GET_BLOCK_POINTER(bb, offset) ((void*)((bb)->buff + (offset)))

static TBufferBlock* _BBGetFirstBlock(const TBlockBuffer *pBB);
static TBufferBlock* _BBGetNextBlock(const TBlockBuffer *pBB, const TBufferBlock *block);
static void _BBReclaimRemovedBlock(TBlockBuffer *pBB);

void BBInitialize(TBlockBuffer *pBB, void *buff, long size)
{
	memset(pBB, 0, sizeof(TCycleBuffer));
	pBB->buff = (U8*)buff;
	pBB->size = size;
}

long BBGetUsedLen(const TBlockBuffer *pBB)
{
	long l = pBB->end - pBB->begin;
	return (l >=0) ? l : (pBB->size + l);
}

long BBGetFreeLen(const TBlockBuffer *pBB)
{
	long l = pBB->begin - pBB->end;
	return (l > 0) ? (l - 1) : (pBB->size + l - 1);
}

void* BBPreallocBlock(const TBlockBuffer *pBB, long len)
{
	long b = pBB->begin;
	long e = pBB->end;
	long s = pBB->size;
	long l = len + sizeof(TBufferBlock);

	long skip = -1;
	long start = -1;

	if (e >= b)
	{
		long r = s - e;
		if (r > l)
			start = e;
		else if (b > l)
		{
			start = 0;
			if (r > sizeof(TBufferBlock))
				skip = r - sizeof(TBufferBlock) - 1;
		}
	}
	else
	{
		if (b - e > l)
			start = e;
	}

	if (start != -1)
	{
		TBufferBlock* header;
		if (skip != -1)
		{
			header = (TBufferBlock*)BB_GET_BLOCK_POINTER(pBB, e);
			header->removed = 1;
			header->length = skip;
		}

		header = (TBufferBlock*)BB_GET_BLOCK_POINTER(pBB, start);
		header->removed = 0;
		header->length = len;

		return BB_GET_BLOCK_DATA(header);
	}
	return NULL;
}

void* BBConformBlock(TBlockBuffer *pBB, void* block, long len)
{
	TBufferBlock* header = BB_GET_BLOCK_HEADER(block);
	if (header->length >= len)
	{
		header->length = len;
		pBB->end =  BB_GET_BLOCK_OFFSET(pBB, block) + len;
		return block;
	}
	return NULL;
}

void* BBAllocBlock(TBlockBuffer *pBB, long len)
{
	void *block = BBPreallocBlock(pBB, len);
	if (block)
		return BBConformBlock(pBB, block, len);
	return NULL;
}

void BBDeleteBlock(TBlockBuffer *pBB, void *block)
{
	TBufferBlock *header = BB_GET_BLOCK_HEADER(block);
	header->removed = 1;
	_BBReclaimRemovedBlock(pBB);
}

void* BBGetFirstBlock(const TBlockBuffer *pBB)
{
	TBufferBlock *header = _BBGetFirstBlock(pBB);
	while (header)
	{
		if (! header->removed)
			return BB_GET_BLOCK_DATA(header);
		header = _BBGetNextBlock(pBB, header);
	}
	return NULL;
}

void* BBGetNextBlock(const TBlockBuffer *pBB, const void *block)
{
	TBufferBlock *header = BB_GET_BLOCK_HEADER(block);
	while (header = _BBGetNextBlock(pBB, header))
	{
		if (! header->removed)
			return BB_GET_BLOCK_DATA(header);
	}
	return NULL;
}

long BBGetBlockLen(const void *block)
{
	return (long)BB_GET_BLOCK_HEADER(block)->length;
}

TBufferBlock* _BBGetFirstBlock(const TBlockBuffer *pBB)
{
	long b = pBB->begin;
	long e = pBB->end;
	long s = pBB->size;
	long start = -1;

	if (e >= b)
	{
		if (e - b >= sizeof(TBufferBlock))
			start = b;
	}
	else
	{
		long r = s - b;
		if (r >= sizeof(TBufferBlock))
			start = b;
		else if (e >= sizeof(TBufferBlock))
			start = 0;
	}

	if (start != -1)
		return (TBufferBlock*)BB_GET_BLOCK_POINTER(pBB, start);
	return NULL;
}

TBufferBlock* _BBGetNextBlock(const TBlockBuffer *pBB, const TBufferBlock *block)
{
	long b = pBB->begin;
	long e = pBB->end;
	long s = pBB->size;
	long start = BB_GET_BLOCK_OFFSET(pBB, block);

	start += sizeof(TBufferBlock) + block->length;

	if (start == e)
		return NULL;

	if (start > e)
	{
		if (s - start > sizeof(TBufferBlock))
			return (TBufferBlock*)BB_GET_BLOCK_POINTER(pBB, start);

		start = 0;
	}

	if (e - start >= sizeof(TBufferBlock))
		return (TBufferBlock*)BB_GET_BLOCK_POINTER(pBB, start);
	return NULL;
}

void _BBReclaimRemovedBlock(TBlockBuffer *pBB)
{
	TBlockBuffer BB;
	memcpy(&BB, pBB, sizeof(BB));

	TBufferBlock *header = _BBGetFirstBlock(&BB);
	while (header)
	{
		if (! header->removed)
			break;
		header = _BBGetNextBlock(&BB, header);
	}

	if (header)
		pBB->begin = BB_GET_BLOCK_OFFSET(&BB, header);
	else
		pBB->begin = BB.end;
}



//////////////////////////////////////////////////////////////////////
//	class CBlockBuffer

CBlockBuffer::CBlockBuffer()
{
	memset(&m_CB, 0, sizeof(m_CB));
	m_bOwnMemory = FALSE;
	m_pWriteLock = NULL;
	m_pReadLock = NULL;
}

CBlockBuffer::CBlockBuffer(long nSize, void *pBuff/*=NULL*/, 
	BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/)
{
	Init(nSize, pBuff, bParellelWrite, bParellelRead);
}

CBlockBuffer::~CBlockBuffer()
{
	Uninit();
}

BOOL CBlockBuffer::Init(long nSize, void *pBuff/*=NULL*/, 
	BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/)

{
	memset(&m_CB, 0, sizeof(m_CB));
	if (pBuff)
	{
		m_CB.buff = (U8*)pBuff;
		m_bOwnMemory = FALSE;
	}
	else
	{
		m_CB.buff = new U8 [nSize];
		m_bOwnMemory = TRUE;
	}
	m_CB.size = nSize;

	if (bParellelWrite)
		m_pWriteLock = new CThreadLock (TRUE);
	if (bParellelRead)
		m_pReadLock = new CThreadLock (TRUE);

	return TRUE;
}

BOOL CBlockBuffer::Uninit()
{
	if (m_bOwnMemory && m_CB.buff)
		delete [] m_CB.buff;
	memset(&m_CB, 0, sizeof(m_CB));
	m_bOwnMemory = FALSE;

	if (m_pWriteLock)
		delete m_pWriteLock;
	m_pWriteLock = NULL;

	if (m_pReadLock)
		delete m_pReadLock;
	m_pReadLock = NULL;

	return TRUE;
}

BOOL CBlockBuffer::IsInited()
{
	return (m_CB.buff != NULL);
}

long CBlockBuffer::GetUsedLen()
{
	return BBGetUsedLen(&m_CB);
}

long CBlockBuffer::GetFreeLen()
{
	return BBGetFreeLen(&m_CB);
}

void* CBlockBuffer::PreallocBlock(long len)
{
	if (m_pWriteLock)
		m_pWriteLock->Lock();

	void *data = BBPreallocBlock(&m_CB, len);

	if (m_pWriteLock)
		m_pWriteLock->Unlock();
	return data;
}

void* CBlockBuffer::ConformBlock(void* block, long len)
{
	if (m_pWriteLock)
		m_pWriteLock->Lock();

	void *data = BBConformBlock(&m_CB, block, len);

	if (m_pWriteLock)
		m_pWriteLock->Unlock();
	return data;
}

void* CBlockBuffer::AllocBlock(long len)
{
	if (m_pWriteLock)
		m_pWriteLock->Lock();

	void *data = BBAllocBlock(&m_CB, len);

	if (m_pWriteLock)
		m_pWriteLock->Unlock();
	return data;
}

void CBlockBuffer::DeleteBlock(void *block)
{
	if (m_pReadLock)
		m_pReadLock->Lock();

	BBDeleteBlock(&m_CB, block);

	if (m_pReadLock)
		m_pReadLock->Unlock();
}

void* CBlockBuffer::GetFirstBlock()
{
	if (m_pReadLock)
		m_pReadLock->Lock();

	void *data = BBGetFirstBlock(&m_CB);

	if (m_pReadLock)
		m_pReadLock->Unlock();
	return data;
}

void* CBlockBuffer::GetNextBlock(const void *block)
{
	if (m_pReadLock)
		m_pReadLock->Lock();

	void *data = BBGetNextBlock(&m_CB, block);

	if (m_pReadLock)
		m_pReadLock->Unlock();
	return data;
}

long CBlockBuffer::GetBlockLen(const void *block)
{
	return BBGetBlockLen(block);
}


