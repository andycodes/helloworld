#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
 #include <unistd.h>

int  main(void)
{
	int fd, num;
	fd = open("/dev/waitq", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != - 1) {
		while (1) {
			read(fd, &num, sizeof(int)); //程序将阻塞在此语句，除非有针对globalvar的输入
			printf("The globalvar is %d\n", num);
			//如果输入是0，则退出
			if (num == 0){
				close(fd);
				break;
			}
		}
	}else
		printf("device open failure\n");

	return 0;
}


