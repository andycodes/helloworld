#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include <iostream>
using namespace std;

#pragma pack(1)
typedef struct ioctl_test {
	int a;
	char b;
	long long c;
	char * data_addr;
}ioctl_test_t;
#pragma pack()   // »Ö¸´×Ö½Ú¶ÔÆë

int main(void)
{
	int fd, ret;
	ioctl_test_t tt;
	tt.a = 0x12345678;
	tt.b = 0x55;
	tt.c = 0x1234567812345678;
	tt.data_addr = (char*)malloc(8);
	memset((void*)tt.data_addr, 0, 8);
	*(tt.data_addr + 5) = 5;

	fd = open("/dev/ioctrl_test", 0);
	if (fd < 0) {
		perror("open device leds");
		exit(1);
	}


	unsigned long id = 1;
	ret = ioctl(fd, 0, &id);
	if (ret) {
		cout << "ioctl0:" <<ret<<endl;
		goto T_FIN;
	}
	cout << "id:" <<id<<endl;

	ret = ioctl(fd, 1, &tt);
	if (ret){
		cout << "ioctl" <<ret<<endl;
	}

T_FIN:
	close(fd);
	free(tt.data_addr);
	return 0;
}

