#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
 #include <unistd.h>

int  main(void)
{
	int fd, num;
	fd = open("/dev/waitq", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != - 1){
		while (1){
			printf("Please input the globalvar:\n");
			scanf("%d", &num);
			write(fd, &num, sizeof(int));
			//如果输入0，退出
			if (num == 0) {
				close(fd);
				break;
			}
		}
	}else
		printf("device open failure\n");

	return 0;
}

