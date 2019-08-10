// PlatformWraper.cpp: implementation of the CPlatformWraper class.
//
//////////////////////////////////////////////////////////////////////

#include "platform.h"
//#include "util_string.h"


////////////////////////////////////////////////////////////////////////////////
//	platform independent functions



#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syslog.h>
#include <errno.h>
#include <stdlib.h>

TOSProcessID OSDaemonize(BOOL close_io/*=TRUE*/)
{
	pid_t pid = fork();

	/* parent exits , child continues */
	if (pid != 0)
		return (TOSProcessID)pid;

	setsid(); /* become session leader */

	if (close_io)
	{
		int i;
		for(i=0;i< NOFILE ;++i) /* close STDOUT, STDIN, STDERR, */
			close(i);
	}

	umask(0); /* clear file mode creation mask */
	return (TOSProcessID)0;
}


#define MAX_PARAM_COUNT 100
int OSSystemCmd(const char *cmd)
{
	return system(cmd);
}

const char* OSGetEnv(const char *name)
{
	return (const char*)getenv(name);
}

BOOL OSSetEnv(const char *name, const char *value)
{
	return 0 == setenv(name, value, TRUE);
}

BOOL OSRemoveEnv(const char *name)
{
	return 0 == unsetenv(name);
}

U32 OSRandom(U32 range/*=0*/)
{
	static BOOL s_bInited = FALSE;
	if (! s_bInited)
	{
		srand((int)time(NULL));
		s_bInited = TRUE;
	}
	if (range != 0)
		return (U32)((rand()/(RAND_MAX + 1.0))*range);
	return (U32)rand();
}

BOOL OSSleep(U32 nMS)
{
	usleep(nMS * 1000);
	return TRUE;
}

void OSSetSignalHandler(int sig, FOnSignal fOnSignal)
{
	signal(sig, fOnSignal);
}


int OSReadFile(TOSFileHandle file, void *buff, int len)
{
	int n, l = len;
	U8 *p = (U8*)buff;

	while (l > 0)
	{
		n = read(file, p, l);
		if (n < 0)
		{
//			perror("read error ");
			if (errno == EINTR)
				n = 0;
			else
				return -1;
		}
		else if (n == 0)
			break;

		p += n;
		l -= n;
	}

	return len - l;
}

int OSWriteFile(TOSFileHandle file, const void *buff, int len)
{
	int n, l = len;
	U8 *p = (U8*)buff;

	while (l > 0)
	{
		n = write(file, p, l);
		if (n <= 0)
		{
//			perror("write error ");
			if (errno == EINTR)
				n = 0;
			else
				return -1;
		}

		p += n;
		l -= n;
	}

	return len;
}

int OSReadFileDatagram(TOSFileHandle file, void *buff, int len)
{
	while (1)
	{
		int n = read(file, buff, len);
		if (n >= 0)
			return n;
		else if (errno != EINTR)
			return -1;
	}
	return -1;
}

int OSWriteFileDatagram(TOSFileHandle file, const void *buff, int len)
{
	while (1)
	{
		int n = write(file, buff, len);
		if (n > 0)
			return n;
		else if (errno != EINTR)
			return -1;
	}
	return -1;
}

TOSFileHandle OSDuplicateFile(TOSFileHandle file)
{
	return dup(file);
}

BOOL OSCloseFile(TOSFileHandle file)
{
	close(file);
	return TRUE;
}

int OSReadFileLine(TOSFileHandle file, void *buff, int len)
{
	int nLen = 0;
	char *p = (char*)buff;

	while (nLen < len)
	{
		if (1 == OSReadFile(file, p, 1))
		{
			nLen ++;
			if ((*p) == '\n')
				return nLen;
		}
		else
			return -1;
		p ++;
	}
	return nLen;
}

