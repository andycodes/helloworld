#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define DPI_NETLINK 28
#define CONTROL_MSG 0x10
#define DATA_MSG 0x11

#define	USER_SPACE_STRING		"NIHAO KERNEL"
	
struct _data_to_kernel {
	char pskb_ptr[100];
};
   

struct _data_from_kernel {
	char pskb_ptr[100];
};


int main()
{

	//netlink's data
	int sock_fd;
	struct sockaddr_nl src_addr, dest_addr;  
	struct nlmsghdr *send_nlh = NULL;  //netlink header  
	struct nlmsghdr *rev_nlh = NULL;   //netlink header  
	struct iovec send_iov,rev_iov;  
	struct msghdr rev_msg,send_msg;

	struct _data_from_kernel paddr;    //defined in dpi_mem_pool.h
	struct _data_from_kernel data_from_kernel;
	struct _data_to_kernel data_to_kernel;			//defined in qos_pme.h

	int i;
	int fd;
	int ret1;

	strncpy((char *)data_to_kernel.pskb_ptr,USER_SPACE_STRING, sizeof(USER_SPACE_STRING));
	//creat netlink socket
	sock_fd = socket(PF_NETLINK, SOCK_RAW, DPI_NETLINK);
	 //init_netlinksocket(sock_fd,src_addr,dest_addr,send_nlh,send_iov,send_msg,rev_nlh,rev_iov,rev_msg);

	//init socket src addr
	memset(&src_addr, 0, sizeof(src_addr));  
	 src_addr.nl_family = AF_NETLINK;  
	 src_addr.nl_pid = getpid( );   //self pid   
	 src_addr.nl_groups = 0;    
	 bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));

	//fcntl(sock_fd, F_SETFL, O_NONBLOCK); //notice!

	//init socket dest addr  
	memset(&dest_addr, 0, sizeof(dest_addr));  
	dest_addr.nl_family = AF_NETLINK;  
	dest_addr.nl_pid = 0;   //  To Linux Kernel   
	dest_addr.nl_groups = 0; //unicast 


	//init netlink head send_nlh
	send_nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(sizeof(data_to_kernel)));
	send_nlh->nlmsg_len = NLMSG_SPACE(sizeof(data_to_kernel));
	send_nlh->nlmsg_pid = getpid();  
	send_nlh->nlmsg_flags = 0;  
	send_nlh->nlmsg_type =CONTROL_MSG; //NOTICE          

	//init send_msg 	
	memcpy(NLMSG_DATA(send_nlh), &data_to_kernel,sizeof(data_to_kernel));
	memset(&send_msg, 0, sizeof(send_msg));
	send_iov.iov_base = (void *)send_nlh; //NOTICE  
	send_iov.iov_len = send_nlh->nlmsg_len;  
	send_msg.msg_name = (void *)&dest_addr;  
	send_msg.msg_namelen = sizeof(dest_addr);  
	send_msg.msg_iov = &send_iov;  
	send_msg.msg_iovlen = 1;

	//通知内核进程ID等，初始化netlink
	for(i=0;i<2;i++)
		sendmsg(sock_fd, &send_msg, 0);

	send_nlh->nlmsg_type =DATA_MSG;//NOTICE!

	//=============init netlink head rev_nlh ==============================================
	rev_nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(sizeof(struct _data_from_kernel)));
	rev_nlh->nlmsg_len = NLMSG_SPACE(sizeof(struct _data_from_kernel));
	rev_nlh->nlmsg_pid = getpid();  /* self pid */  
	rev_nlh->nlmsg_flags = 0;  
	rev_nlh->nlmsg_type = 0; //NOTICE         
	//init rev_msg  
	//memcpy(NLMSG_DATA(rev_nlh), &data_to_user,sizeof(data_to_user));
	//memset(&rev_msg, 0, sizeof(rev_msg));
	rev_iov.iov_base = (void *)rev_nlh; //NOTICE	
	rev_iov.iov_len = rev_nlh->nlmsg_len;	
	rev_msg.msg_name = (void *)&dest_addr;	
	rev_msg.msg_namelen = sizeof(dest_addr);	
	rev_msg.msg_iov = &rev_iov;	
	rev_msg.msg_iovlen = 1;
	//rev_msg.msg_flags=MSG_DONTWAIT;



	while(1) {
		memset(rev_nlh, 0, NLMSG_SPACE(sizeof(struct _data_from_kernel)));
		//recvmsg(sock_fd, &rev_msg, O_NONBLOCK);
		ret1=recvmsg(sock_fd, &rev_msg, 0);
		if(ret1>=0) {
			memcpy(&paddr,NLMSG_DATA(rev_nlh), 100);
			printf("[%s]_data_from_kernel: [%s]\n", __func__, paddr.pskb_ptr);
			memcpy(NLMSG_DATA(send_nlh), &data_to_kernel,sizeof(struct _data_to_kernel));
			sendmsg(sock_fd, &send_msg, 0);
		}//end if(ret1>=0)
	}//end while(1)

	    return 0;
}

