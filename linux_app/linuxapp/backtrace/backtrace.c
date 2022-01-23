#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>	/* backtrace* */
#include <fcntl.h>		/*O_RDWR*/
#include <unistd.h>	/*close*/
#include <string.h>	/*strlen*/
#include <signal.h>	/*SIGSEGV*/


#include <memory.h>
#include <ucontext.h>
#include <dlfcn.h>

#define DUMP_FUN_POINT_SIZE	(30)


void func_c()
{
	*((volatile char*)0x0) = 0;
}

void func_b()
{
	func_c();
}

void func_a()
{
	func_b();
}


void dump_to_print(void)
{
    void*		array[DUMP_FUN_POINT_SIZE];
    size_t 	size;
    char**		strings;
    size_t 	i;

/*
backtrace() returns a backtrace for the calling program, in  the  array
       pointed  to  by  buffer.  A backtrace is the series of currently active
       function calls for the program.  Each item in the array pointed  to  by
       buffer  is  of  type  void *, and is the return address from the corre‐
       sponding stack frame.  The size argument specifies the  maximum  number
       of  addresses that can be stored in buffer.  If the backtrace is larger
       than size, then the addresses corresponding to  the  size  most  recent
       function  calls  are  returned;  to obtain the complete backtrace, make
       sure that buffer and size are large enough.
*/
    size = backtrace(array,DUMP_FUN_POINT_SIZE);
/*
Given the set of addresses returned by  backtrace()  in  buffer,  back‐
       trace_symbols()  translates the addresses into an array of strings that
       describe the addresses symbolically.  The size argument  specifies  the
       number  of  addresses  in  buffer.  The symbolic representation of each
       address consists of the function name (if this can  be  determined),  a
       hexadecimal offset into the function, and the actual return address (in
       hexadecimal).  The address of the array of string pointers is  returned
       as  the  function  result  of  backtrace_symbols().  This array is mal‐
       loc(3)ed by backtrace_symbols(), and must be freed by the caller.  (The
       strings  pointed to by the array of pointers need not and should not be
       freed.)

*/
    strings = backtrace_symbols(array, size);

    fprintf(stderr,"Obtained %zd stack frames.nm", size);

    for(i =0; i < size; i++)
        fprintf (stderr,"%s \n", strings[i]);

    free (strings);
}


void dump_to_file(void)
{
	void *array[DUMP_FUN_POINT_SIZE];
	size_t size;
	int fd;
	char buf[64];


	printf("[%s]\n", __func__);
	fd = open("./bt1.txt", O_CREAT|O_RDWR|O_APPEND);
	if (fd < 0)
	{
		perror("open file failed");
		exit(0);
	}
	size = backtrace(array, DUMP_FUN_POINT_SIZE);
	backtrace_symbols_fd(array, size, fd);
	write(fd, "\n", 1);
	close(fd);
}


/*GCC提供了两个内置函数用来在运行时取得函数调用栈中
的返回地址和框架地址
GCC:6.49 Getting the Return or Frame Address of a Function*/
void showBacktrace()
{
        void * ret = __builtin_return_address(1);
        printf("ret address [%p]\n", ret);
        void * caller = __builtin_frame_address(0);
        printf("call address [%p]\n", caller);
}


void dump(int signo)
{
	dump_to_print();
	dump_to_file();
	showBacktrace();
	exit(0);
}

int main()
{
	signal(SIGSEGV,&dump);
	func_a();
	return 0;
}

/*
注：选项 -rdynamic 可用来通知链接器
将所有符号添加到动态符号表中，
如果你的链接器支持-rdynamic的话，
建议将其加上，即
# gcc -rdynamic -g backtraces.c -o backtrace
*/
/*
GDB调试的时候出现了：
Program received signal SIGSEGV, Segmentation fault.（程序收到信号SIGSEGV，分段故障）
  SIGSEGV：在POSIX兼容的平台上，SIGSEGV是当一个进
  程执行了一个无效的内存引用，或发生段错误
  时发送给它的信号。SIGSEGV的符号常量在头文件
  signal.h中定义。因为在不同平台上，信号数字可能变化，
  因此符号信号名被使用。通常，它是信号#11。
*/
