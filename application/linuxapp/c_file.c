#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>

void WriteFormatted (FILE * stream, const char * format, ...)
{
	va_list args;
	va_start (args, format);
	vfprintf (stream, format, args);
	va_end (args);
}


void test_vfprintf (void)
{
	FILE * pFile;

	pFile = fopen ("myfile.txt","w");
	if (NULL == pFile)
		return;

	WriteFormatted (pFile,"Call with %d variable argument.\n",1);
	WriteFormatted (pFile,"Call with %d variable %s.\n",2,"arguments");

	fclose (pFile);
}


void test_stat(void)
{
	struct stat buf;
	stat("myfile.txt", &buf);
	printf("file size = %ld\n", buf.st_size);
}

void test_fgets(void)
{
	FILE * pFile;
	char s[1024];

	pFile = fopen ("myfile.txt","r");
	if (NULL == pFile) {
		printf(" file not find\n");
		return;
	}

	while((fgets(s,1024,pFile))!=NULL)
	{
		printf("%s",s);
	}

	fclose (pFile);
}


int main(int argc, char *argv[])
{
	test_vfprintf();
	test_fgets();
	test_stat();

	return 0;
}

