//	msg_pool.cpp

#include "msg_pool.h"

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/msg.h>


TRawMsg* AssembleMsg(void* buffer, int buffer_size, U32 type, I32 len, const void *param)
{
	if ((len>0?len:0) + sizeof(TRawMsg) > buffer_size)
		return NULL;

	TRawMsg *msg = (TRawMsg*)buffer;
	msg->__spare = 1;
	msg->type = type;
	msg->len = len;
	if ((len > 0) && param)
		memcpy(MSG_PARAM(msg), param, len);
	return msg;
}

IMsgPool::~IMsgPool()
{
}

//////////////////////////////////////////////////////////////////////
//	class CCycleMsgPool

CMsgPoolBuffer::CMsgPoolBuffer()
{
}

CMsgPoolBuffer::~CMsgPoolBuffer()
{
}

BOOL CMsgPoolBuffer::Init(long nSize, void *pBuff/*=NULL*/, 
		BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/)
{
	return CCycleBuffer::Init(nSize, pBuff, bParellelWrite, bParellelRead, TRUE, TRUE);
}

BOOL CMsgPoolBuffer::WriteMsg(TRawMsg *msg)
{
	return WriteData(MSG_DATA(msg), MSG_DATA_LEN(msg));
}

BOOL CMsgPoolBuffer::ReadMsg(TRawMsg *msg, I32 buff_size)
{
	if (m_pReadLock)
		m_pReadLock->Lock();

	I32 len = buff_size - sizeof(TRawMsg);

	//read header
	BOOL bResult = ReadData(MSG_HEADER(msg), MSG_HEADER_LEN);

	if (bResult)
	{
		if (msg->len > 0)
		{
			// read parameter
			if (msg->len <= len)
				bResult = ReadData(MSG_PARAM(msg), msg->len);
			else
			{
				ReadData(NULL, msg->len);
				bResult = FALSE;
			}
		}
	}

	if (m_pReadLock)
		m_pReadLock->Unlock();
	return bResult;
}



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolPipe

CMsgPoolFile::CMsgPoolFile()
{
	m_fileIn = INVALID_FILE_HANDLE;
	m_fileOut = INVALID_FILE_HANDLE;
	m_pWriteLock = NULL;
	m_pReadLock = NULL;
}

CMsgPoolFile::~CMsgPoolFile()
{
	Uninit();
}

BOOL CMsgPoolFile::Init(TOSFileHandle fileIn, TOSFileHandle fileOut, 
	BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/)
{
	if ((fileIn != INVALID_FILE_HANDLE) || (fileOut != INVALID_FILE_HANDLE))
	{
		if (fileIn != INVALID_FILE_HANDLE)
			m_fileIn = OSDuplicateFile(fileIn);
		if (fileOut != INVALID_FILE_HANDLE)
			m_fileOut = OSDuplicateFile(fileOut);

		if (bParellelWrite)
			m_pWriteLock = new CThreadLock (TRUE);
		if (bParellelRead)
			m_pReadLock = new CThreadLock (TRUE);

		return TRUE;
	}
	return FALSE;
}

BOOL CMsgPoolFile::Uninit()
{
	if (m_fileIn != INVALID_FILE_HANDLE)
		OSCloseFile(m_fileIn);
	m_fileIn = INVALID_FILE_HANDLE;

	if (m_fileOut != INVALID_FILE_HANDLE)
		OSCloseFile(m_fileOut);
	m_fileOut = INVALID_FILE_HANDLE;

	if (m_pWriteLock)
		delete m_pWriteLock;
	m_pWriteLock = NULL;

	if (m_pReadLock)
		delete m_pReadLock;
	m_pReadLock = NULL;

	return TRUE;
}

BOOL CMsgPoolFile::IsInited()
{
	return ((m_fileIn != INVALID_FILE_HANDLE) || (m_fileOut != INVALID_FILE_HANDLE));
}

BOOL CMsgPoolFile::WriteMsg(TRawMsg *msg)
{
	if (m_fileIn == INVALID_FILE_HANDLE)
		return FALSE;

	if (m_pWriteLock)
		m_pWriteLock->Lock();

	BOOL bResult = 
		(MSG_DATA_LEN(msg) == OSWriteFile(m_fileIn, MSG_DATA(msg), MSG_DATA_LEN(msg)));

	if (m_pWriteLock)
		m_pWriteLock->Unlock();

	return bResult;
}

BOOL CMsgPoolFile::ReadMsg(TRawMsg *msg, I32 buff_size)
{
	if (m_fileOut == INVALID_FILE_HANDLE)
		return FALSE;

	if (m_pReadLock)
		m_pReadLock->Lock();

	I32 len = buff_size - sizeof(TRawMsg);

	//read header
	BOOL bResult = 
		(MSG_HEADER_LEN == OSReadFile(m_fileOut, MSG_HEADER(msg), MSG_HEADER_LEN));

	if (bResult)
	{
		if (msg->len > 0)
		{
			// read parameter
			if (msg->len <= len)
			{
				bResult = 
					(msg->len == OSReadFile(m_fileOut, MSG_PARAM(msg), msg->len));
			}
			else
			{
				OSReadFile(m_fileOut, NULL, msg->len);
				bResult = FALSE;
			}
		}
	}

	if (m_pReadLock)
		m_pReadLock->Unlock();
	return bResult;
}



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolPipe


BOOL CMsgPoolPipe::Init(BOOL bParellelWrite/*=FALSE*/, BOOL bParellelRead/*=FALSE*/)
{
	BOOL bResult = FALSE;
	TOSFileHandle fds[2];

	if (-1 != pipe(fds))
	{
		bResult = CMsgPoolFile::Init(fds[1], fds[0], bParellelWrite, bParellelRead);
		OSCloseFile(fds[0]);
		OSCloseFile(fds[1]);
	}
	return bResult;
}



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolUnix

CMsgPoolUnix::CMsgPoolUnix()
{
	m_fileIn = INVALID_FILE_HANDLE;
	m_fileOut = INVALID_FILE_HANDLE;
}

CMsgPoolUnix::~CMsgPoolUnix()
{
	Uninit();
}

BOOL CMsgPoolUnix::Init()
{
	TOSFileHandle fds[2];
	if (-1 != socketpair(AF_LOCAL, SOCK_DGRAM, 0, fds))
	{
		m_fileIn = fds[1];
		m_fileOut = fds[0];

		return TRUE;
	}
	return FALSE;
}

BOOL CMsgPoolUnix::Init(TOSFileHandle fileIn, TOSFileHandle fileOut)
{
	if ((fileIn != INVALID_FILE_HANDLE) || (fileOut != INVALID_FILE_HANDLE))
	{
		if (fileIn != INVALID_FILE_HANDLE)
			m_fileIn = OSDuplicateFile(fileIn);
		if (fileOut != INVALID_FILE_HANDLE)
			m_fileOut = OSDuplicateFile(fileOut);

		return TRUE;
	}
	return FALSE;
}

BOOL CMsgPoolUnix::Uninit()
{
	if (m_fileIn != INVALID_FILE_HANDLE)
		OSCloseFile(m_fileIn);
	m_fileIn = INVALID_FILE_HANDLE;

	if (m_fileOut != INVALID_FILE_HANDLE)
		OSCloseFile(m_fileOut);
	m_fileOut = INVALID_FILE_HANDLE;

	return TRUE;
}

BOOL CMsgPoolUnix::IsInited()
{
	return (m_fileIn != INVALID_FILE_HANDLE);
}

BOOL CMsgPoolUnix::WriteMsg(TRawMsg *msg)
{
	if (m_fileIn == INVALID_FILE_HANDLE)
		return FALSE;

	BOOL bResult = 
		(MSG_DATA_LEN(msg) == OSWriteFileDatagram(m_fileIn, MSG_DATA(msg), MSG_DATA_LEN(msg)));

	return bResult;
}

BOOL CMsgPoolUnix::ReadMsg(TRawMsg *msg, I32 buff_size)
{
	if (m_fileOut == INVALID_FILE_HANDLE)
		return FALSE;

	//read datagram
	I32 len = OSReadFileDatagram(m_fileOut, MSG_DATA(msg), buff_size - MSG_SPARE_LEN);
	BOOL bResult = (len >= MSG_HEADER_LEN) && (len == MSG_DATA_LEN(msg));
	if (!bResult)
		printf("unix read error, len=%d, msg_len=%d\n", len, msg->len);
	return bResult;
}



//////////////////////////////////////////////////////////////////////
//	class CMsgPoolQueue

CMsgPoolQueue::CMsgPoolQueue()
{
	m_nQueueID = -1;
}

CMsgPoolQueue::~CMsgPoolQueue()
{
	Uninit();
}

BOOL CMsgPoolQueue::Init()
{
    /*IPC_PRIVATE:创建新的共享内存*/
    int id = msgget(IPC_PRIVATE, 0);
	if (id != -1)
	{
		m_nQueueID = id;
		return TRUE;
	}
	return FALSE;/*-1 失败*/
}

BOOL CMsgPoolQueue::Uninit()
{
/*IPC_RMID:从系统内核中移走消息队列*/
    if (m_nQueueID != -1)
		msgctl(m_nQueueID, IPC_RMID, NULL);
	m_nQueueID = -1;

	return TRUE;
}

BOOL CMsgPoolQueue::IsInited()
{
	return (m_nQueueID != -1);
}


BOOL CMsgPoolQueue::WriteMsg(TRawMsg *msg)
{
	if (m_nQueueID == -1)
		return FALSE;

	msg->__spare = 1;
	BOOL bResult = (0 == msgsnd(m_nQueueID, msg, MSG_DATA_LEN(msg), 0));

	return bResult;
}

BOOL CMsgPoolQueue::ReadMsg(TRawMsg *msg, I32 buff_size)
{
	if (m_nQueueID == -1)
		return FALSE;

	int len = msgrcv(m_nQueueID, msg, buff_size - MSG_SPARE_LEN, 0, 0);
	BOOL bResult = (len >= MSG_HEADER_LEN) && (len == MSG_DATA_LEN(msg));

	return bResult;
}



