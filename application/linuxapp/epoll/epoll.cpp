/*client_send.pl 是发送测试函数*/

#include  <iostream>
#include  <sys/socket.h>
#include  <sys/epoll.h>
#include  <netinet/in.h>
#include  <arpa/inet.h>
#include  <fcntl.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <errno.h>
#include <stdlib.h>
#include <strings.h>

using namespace std;

#define MAXLINE  5
#define OPEN_MAX  100
#define LISTENQ  20
#define SERV_PORT  5000
#define INFTIM  1000

void setnonblocking( int  sock)
{
     int  opts;
    opts = fcntl(sock,F_GETFL);
     if (opts < 0 )
    {
        perror( " fcntl(sock,GETFL) " );
         exit ( 1 );
    }
    opts  =  opts|O_NONBLOCK;
     if (fcntl(sock,F_SETFL,opts) < 0 )
    {
        perror( " fcntl(sock,SETFL,opts) " );
         exit ( 1 );
    }
}


/*
typedef union epoll_data {
               void    *ptr;
               int      fd;
               uint32_t u32;
               uint64_t u64;
           } epoll_data_t;

           struct epoll_event {
               uint32_t     events;
               epoll_data_t data;
           };
*/

int  main(void)
{
	int  i,listenfd, connfd, sockfd,epfd,nfds;
	ssize_t n;
	char line[MAXLINE];
	socklen_t clilen;
	// 声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
	struct epoll_event ev,events[20];
	// 生成用于处理accept的epoll专用的文件描述符
	/*open an epoll file descriptor*/
	epfd = epoll_create(256);
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	listenfd  =  socket(AF_INET, SOCK_STREAM,  0);

	/*将listenfd socket 句柄加入到监控队列中*/
	ev.data.fd = listenfd;
	// 设置要处理的事件类型
	/*EPOLLIN : 可读事件*/
	/*EPOLLET : 设置为ET模式；默认为LT模式*/
	ev.events = EPOLLIN|EPOLLET;
	/*EPOLL_CTL_ADD 注册epoll事件*/
	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd, &ev);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family  =  AF_INET;
	const char  * local_addr = " 127.0.0.1 " ;
	inet_aton(local_addr, & (serveraddr.sin_addr)); // htons(SERV_PORT);
	serveraddr.sin_port = htons(SERV_PORT);
	bind(listenfd,(sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(listenfd, LISTENQ);

	while(1) {
/*等待epoll事件的发生
          epfd 句柄
          epoll_event *events 事件类型
          maxevents 最大事件数目
          timeout   超时
*/
		nfds = epoll_wait(epfd, events, 20, 500);
		if(-1 == nfds)
			perror( " epoll_wait err\n");
// 处理所发生的所有事件
		for (i = 0 ;i < nfds; ++ i) {
			if (events[i].data.fd == listenfd) {
				clilen = sizeof(struct sockaddr);
				connfd = accept(listenfd,(struct sockaddr  * )&clientaddr,  &clilen);
				if (connfd < 0) {
					perror(" connfd<0 ");
					exit (1);
				}

				char  * str  =  inet_ntoa(clientaddr.sin_addr);
				cout  <<   " accapt a connection from  "   <<  str  <<  endl;

				/*将accept socket 句柄加入到监控队列中*/
				// 设置用于读操作的文件描述符
				ev.data.fd = connfd;
				 // 设置用于注测的读操作事件
				ev.events = EPOLLIN|EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_ADD,connfd, &ev);
			}else if (events[i].events & EPOLLIN) {
				cout  <<   " EPOLLIN "   <<  endl;
				if  ((sockfd  =  events[i].data.fd)  <  0)
					continue;

				if  ((n  =  read(sockfd, line, MAXLINE))  <  0){
					if  (errno  ==  ECONNRESET) {
						close(sockfd);
						events[i].data.fd  =   -1 ;
					} else
						std::cout << " readline error " << std::endl;
				}else if(n  == 0) {
					close(sockfd);
					events[i].data.fd  =   -1 ;
				}

				line[n]  =   '\0';
				cout  <<   " read  "   <<  line  <<  endl;
			}else if (events[i].events & EPOLLOUT) {
				sockfd  =  events[i].data.fd;
				write(sockfd, line, n);
				// 设置用于读操作的文件描述符
				ev.data.fd = sockfd;
				// 设置用于注测的读操作事件
				ev.events = EPOLLIN|EPOLLET;
				// 修改sockfd上要处理的事件为EPOLIN
				epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd, & ev);
			}
		}
	}

	return  0 ;
}


/*epoll有两种模式,Edge Triggered(简称ET)
和 Level Triggered(简称LT).在采用这两种模式时要注意的是,
如果采用ET模式,那么仅当状态发生变化时才会通知,
而采用LT模式类似于原来的 select/poll操作,只要还有没有处理的事件就会一直通知.*/

/*client_send.pl*/
/*下面给出测试所用的Perl写的client端,
在client中发送10字节的数据,同时让client
在发送完数据之后进入死循环,
也就是在发送完之后连接的状态不发生改变--既不再发送数据,
也不关闭连接,这样才能观察出server的状态:
运行server和client发现,server仅仅读取了5字节的数据,
而client其实发送了10字节的数据,也就是说,server仅当第一次监听到
了EPOLLIN事件,由于没有读取完数据,而且采用的是ET模式,状态在此之后不
发生变化,因此server再也接收不到EPOLLIN事件了.
(友情提示:上面的这个测试客户端,当你关闭它的时候会再次出发IO可读事件
给server,此时server就会去读取剩下的5字节数据了,但是这一事件与前面描
述的ET性质并不矛盾.)
*/

/*client_send_sleep.pl*/
/*可以发现,在server接收完5字节的数据
之后一直监听不到client的事件,
而当client休眠5秒之后重新发送数据,server再次监听到了变化,
只不过因为只是读取了5个字节,仍然有10个字节的数据
(client第二次发送的数据)没有接收完.*/

/*如果上面的实验中,对accept的socket都采用的是LT模式,
那么只要还有数据留在buffer中,server就会继续得到通知,
读者可以自行改动代码进行实验.
基于这两个实验,可以得出这样的结论:ET模式仅当状态发生变化的时候才获得通知,
这里所谓的状态的变化并不包括缓冲区中还有未处理的数据,也就是说,如果要采用ET模式,
需要一直read/write直到出错为止,很多人反映为什么采用ET模式只接收了
一部分数据就再也得不到通知了,大多因为这样;而LT
模式是只要有数据没有处理就会一直通知下去的.
补充说明一下这里一直强调的"状态变化"是什么:
1)对于监听可读事件时,如果是socket是监听socket,
那么当有新的主动连接到来为状态发生变化;对一般的socket而言,
协议栈中相应的缓冲区有新的数据为状态发生变化.但是,
如果在一个时间同时接收了N个连接(N>1),但是监听socket只accept了一个连接,
那么其它未 accept的连接将不会在ET模式下给监听socket发出通知,此时状态不发生变化;
对于一般的socket,就如例子中而言,如果对应的缓冲区本身已经有了N字节的数据,
而只取出了小于N字节的数据,那么残存的数据不会造成状态发生变化.
2)对于监听可写事件时,同理可推,不再详述.
而不论是监听可读还是可写,对方关闭socket连接都将造成状态发生变化,
比如在例子中,如果强行中断client脚本,也就是主动中断了socket连接,那么
都将造成server端发生状态的变化,从而server得到通知,将已经在本方缓冲区中的数据读出.
把前面的描述可以总结如下:仅当对方的动作(发出数据,关闭连接等)
造成的事件才能导致状态发生变化,而本方协议栈中已经处理的事件
(包括接收了对方的数据,接收了对方的主动连接请求)并不是造成状态发生变化的必要条件,
状态变化一定是对方造成的.所以在ET模式下的,必须一直处理到出错或者完全处理完毕,
才能进行下一个动作,否则可能会发生错误.
另外,从这个例子中,也可以阐述一些基本的网络编程概念.
首先,连接的两端中,一端发送成功并不代表着对方上层应用程序接收成功,
就拿上面的client测试程序来说,10字节的数据已经发送成功,
但是上层的server并没有调用read读取数据,因此发送成功仅仅说明了数据被对方
的协议栈接收存放在了相应的buffer中,而上层的应用程序是否接收了这部分数据不得而知;
同样的,读取数据时也只代表着本方协议栈的对应 buffer中有数据可读,
而此时时候在对端是否在发送数据也不得而知.
*/

