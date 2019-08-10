#include <stdio.h>
#include "platform.h"
#include "plat_thread.h"
#include "msg_pool.h"

#define MSG_LEN 100
#define MAX_TIME (60*5)



CThreadLock g_lock;
//CThreadChunkSem g_sem(0, TRUE);
IMsgPool *g_pPool = NULL;

long g_read_count = 0;
long g_write_count = 0;
long g_read_bytes = 0;
long g_write_bytes = 0;

long long g_total_count = 0;
long long g_total_bytes = 0;
long g_total_time = 0;

struct TTestMsg : public TRawMsg
{
	U8 content[];
};

class CReadLoop : public CLoopThread
{
public:
	long m_value;

	CReadLoop(long value) {m_value = value;}

	BOOL DoLoop(U32 nLoopCount, long *pnResult)
	{
		U8 buff[10000];
		TTestMsg &msg = *(TTestMsg*)buff;
		I32 len = sizeof(buff);
		int i;

//		g_lock.Lock();
//		printf("Read(%d) Quering\n", m_value);
//		g_lock.Unlock();

//		g_sem.Obtain(m_value);
		int r = 0;
		if (g_pPool->ReadMsg(&msg, len))
		{
			if (msg.type == (U32)msg.len)
			{
				for (i = 0; i < msg.len; i ++)
				{
					if (msg._param[i] != (U8)(U32)i)
					{
						r = 2;
						break;
					}
				}
			}
			else
				r = 1;
				
		}

		if (r != 0)
			printf("Error Reading, error = %d\n", r);

		g_lock.Lock();
		g_read_count += 1;
		g_read_bytes += MSG_DATA_LEN(&msg);
//		printf("Read(%d) Reading, len = %d\n", m_value, len);
		g_lock.Unlock();

//		OSSleep(1000);

		return TRUE;
	}
};

class CWriteLoop : public CLoopThread
{
public:
	long m_value;

	CWriteLoop(long value) {m_value = value;}

	BOOL DoLoop(U32 nLoopCount, long *pnResult)
	{
//		static long s_len = 0;
		U8 buff[10000];
		TTestMsg &msg = *(TTestMsg*)buff;
		int i;

//		g_lock.Lock();
//		printf("Write(%d) Quering\n", m_value);
		msg.len = MSG_LEN;//s_len;
//		s_len = (s_len + 1) % 5;
//		g_lock.Unlock();

		msg.type = msg.len;
		for (i = 0; i < msg.len; i ++)
			msg.content[i] = (U8)(U32)i;

//		g_sem.Release(m_value);
		g_pPool->WriteMsg(&msg);

		g_lock.Lock();
		g_write_count += 1;
		g_write_bytes += MSG_DATA_LEN(&msg);
//		printf("Write(%d) Writing, len = %d\n", m_value, len);
		g_lock.Unlock();

//		OSSleep(500);

		return TRUE;
	}
};


int main(int argc, char* argv[])
{
	const char *pool_type = "buffer";
	if (argc > 1)
		pool_type = argv[1];

	if (strcmpi(pool_type, "queue") == 0)
	{
		printf("Using message queue\n");
		CMsgPoolQueue *pPool = new CMsgPoolQueue();
		pPool->Init();
		g_pPool = pPool;
	}
	else if (strcmpi(pool_type, "unix") == 0)
	{
		printf("Using unix domain socket\n");
		CMsgPoolUnix *pPool = new CMsgPoolUnix();
		pPool->Init();
		g_pPool = pPool;
	}
	else if (strcmpi(pool_type, "pipe") == 0)
	{
		printf("Using pipe file\n");
		CMsgPoolPipe *pPool = new CMsgPoolPipe();
		pPool->Init(TRUE, TRUE);
		g_pPool = pPool;
	}
	else
	{
		printf("Using cycle buffer\n");
		CMsgPoolBuffer *pPool = new CMsgPoolBuffer();
		pPool->Init(1000000, NULL, TRUE, TRUE);
		g_pPool = pPool;
	}
//	printf("sizeof(TRawMsg)=%d\nsizeof(TTestMsg)=%d\n", sizeof(TRawMsg), sizeof(TRawMsg));

	CReadLoop read1(1);
	CReadLoop read2(2);
	CReadLoop read3(3);
	CReadLoop read4(4);
	CReadLoop read5(5);
	CWriteLoop write1(1);
	CWriteLoop write2(2);
	CWriteLoop write3(3);
	CWriteLoop write4(4);
	CWriteLoop write5(5);

	read1.Start();//tspRoundRobin, 50);
//	read2.Start();//tspRoundRobin, 50);
//	read3.Start();//tspRoundRobin, 50);
//	read4.Start();//tspRoundRobin, 50);
//	read5.Start();//tspRoundRobin, 50);
	write1.Start();//tspRoundRobin, 50);
//	write2.Start();//tspRoundRobin, 50);
//	write3.Start();//tspRoundRobin, 50);
//	write4.Start();//tspRoundRobin, 50);
//	write5.Start();//tspRoundRobin, 50);

	while (TRUE)
	{
		OSSleep(1000);

		g_lock.Lock();
		g_total_count += g_read_count;
		g_total_bytes += g_read_bytes;
		g_total_time += 1;

		printf("write = %d(%0.3f mB), read = %d(%0.3f mB)", 
			g_write_count, ((double)g_write_bytes) / 1000000, 
			g_read_count, ((double)g_read_bytes)/1000000);
		printf(", transfer=%0.1fk/s, throughput=%0.3fmB/s\n", 
			((double)g_total_count)/g_total_time/1000, ((double)g_total_bytes)/g_total_time/1000000);

		if (g_total_time >= MAX_TIME)
			break;

		g_write_count = 0;
		g_read_count = 0;
		g_write_bytes = 0;
		g_read_bytes = 0;
		g_lock.Unlock();
	}

//	read1.Join(NULL);
	return 0;
}

