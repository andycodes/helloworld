#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ecall.h"


char kmsg[64]= {0}; 

/*
int argc, char **argv ��������ʱ���������в�������������
argc -- �����в����ܸ��������� ��ִ�г�������
argv[i] -- �� i ��������
argv[0] -- ��ִ�г�������
*/

int main(int argc, char *argv[])
{
	int sockfd;
	int len,i, ret;
	shell_fun_type *fun_ptr;

	if(argc < 2 || argc > 8) {
		printf("parm err\n");
		return -1;		
	}

	fun_ptr = (shell_fun_type *)malloc(sizeof(shell_fun_type)); 
	if (!fun_ptr) {
		printf("fun_test malloc ERR\n");
		return -1;
	}

	memset((void*)fun_ptr, 0, sizeof(shell_fun_type));
	fun_ptr->sign_word = 19831204;
	strncpy((char*)fun_ptr->func_name, (const char*)argv[1], FUNC_NAME_LEN);
	for(i = 0; i< (argc -2); i++) {
		fun_ptr->data.args[i] = atoi(argv[i+2]);
	}

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(sockfd < 0) {
		printf("can not create a socket\n");
		ret = sockfd;
		goto ECALL_ERR;
		
	}

	ret = setsockopt(sockfd, IPPROTO_IP, IMP1_SET, fun_ptr, sizeof(shell_fun_type));
	if (ret) {
		printf("setsockopt err\n");
	}

	free((void*)fun_ptr);
	fun_ptr = NULL;
	close(sockfd);
	return ret;

ECALL_ERR:
	if (fun_ptr) {
		free((void*)fun_ptr);
		fun_ptr = NULL;
	}

	return ret;
}

