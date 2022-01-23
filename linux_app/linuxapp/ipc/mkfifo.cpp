#include <fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <iostream>
using namespace std;

#define FIFO_PATH "/tmp/myfifo"

class ipc_fifo_client{
protected:
		int fd_client;
public:
		ipc_fifo_client(const char *file, int wr) {
			fd_client = open(file, wr);
			if(-1 == fd_client) {
				printf("[%s]open error\n", __func__);
			}
		}

		void doing(void){
			char c;
			printf("[%s]\n", __func__);
			while(c = getchar()) {
				write(fd_client, &c, 1);
			}
	}
};

class ipc_fifo_server {
protected:
		int fd_server;
public:
	char buffer;
	int nread;
	ipc_fifo_server (const char *file, int wr){
		int ret = mkfifo(file, 0777);
		if(ret) {
			printf("[%s]mkfifo error[%d]\n", __func__, ret);
		}

		fd_server = open(file, wr);/*Jam here until the client has launched open action*/
		if(-1 == fd_server) {
			printf("[%s]open error\n", __func__);
		}
	}

	void doing(void){
		printf("[%s]\n", __func__);
		while(1) {
			nread = read(fd_server, &buffer, 1);
			if(nread > 0) {
				buffer = toupper(buffer);/*将小写字母转换为大写*/
				printf("%c", buffer);
			}
		}
	}
};

int main(void){
#if 1
	ipc_fifo_server server(FIFO_PATH, O_RDONLY);
	server.doing();
#else
	ipc_fifo_client client(FIFO_PATH, O_WRONLY);
	client.doing();
#endif

	return 0;
}

