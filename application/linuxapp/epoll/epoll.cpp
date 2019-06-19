/*client_send.pl �Ƿ��Ͳ��Ժ���*/

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
	// ����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�
	struct epoll_event ev,events[20];
	// �������ڴ���accept��epollר�õ��ļ�������
	/*open an epoll file descriptor*/
	epfd = epoll_create(256);
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	listenfd  =  socket(AF_INET, SOCK_STREAM,  0);

	/*��listenfd socket ������뵽��ض�����*/
	ev.data.fd = listenfd;
	// ����Ҫ������¼�����
	/*EPOLLIN : �ɶ��¼�*/
	/*EPOLLET : ����ΪETģʽ��Ĭ��ΪLTģʽ*/
	ev.events = EPOLLIN|EPOLLET;
	/*EPOLL_CTL_ADD ע��epoll�¼�*/
	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd, &ev);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family  =  AF_INET;
	const char  * local_addr = " 127.0.0.1 " ;
	inet_aton(local_addr, & (serveraddr.sin_addr)); // htons(SERV_PORT);
	serveraddr.sin_port = htons(SERV_PORT);
	bind(listenfd,(sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(listenfd, LISTENQ);

	while(1) {
/*�ȴ�epoll�¼��ķ���
          epfd ���
          epoll_event *events �¼�����
          maxevents ����¼���Ŀ
          timeout   ��ʱ
*/
		nfds = epoll_wait(epfd, events, 20, 500);
		if(-1 == nfds)
			perror( " epoll_wait err\n");
// �����������������¼�
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

				/*��accept socket ������뵽��ض�����*/
				// �������ڶ��������ļ�������
				ev.data.fd = connfd;
				 // ��������ע��Ķ������¼�
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
				// �������ڶ��������ļ�������
				ev.data.fd = sockfd;
				// ��������ע��Ķ������¼�
				ev.events = EPOLLIN|EPOLLET;
				// �޸�sockfd��Ҫ������¼�ΪEPOLIN
				epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd, & ev);
			}
		}
	}

	return  0 ;
}


/*epoll������ģʽ,Edge Triggered(���ET)
�� Level Triggered(���LT).�ڲ���������ģʽʱҪע�����,
�������ETģʽ,��ô����״̬�����仯ʱ�Ż�֪ͨ,
������LTģʽ������ԭ���� select/poll����,ֻҪ����û�д�����¼��ͻ�һֱ֪ͨ.*/

/*client_send.pl*/
/*��������������õ�Perlд��client��,
��client�з���10�ֽڵ�����,ͬʱ��client
�ڷ���������֮�������ѭ��,
Ҳ�����ڷ�����֮�����ӵ�״̬�������ı�--�Ȳ��ٷ�������,
Ҳ���ر�����,�������ܹ۲��server��״̬:
����server��client����,server������ȡ��5�ֽڵ�����,
��client��ʵ������10�ֽڵ�����,Ҳ����˵,server������һ�μ�����
��EPOLLIN�¼�,����û�ж�ȡ������,���Ҳ��õ���ETģʽ,״̬�ڴ�֮��
�����仯,���server��Ҳ���ղ���EPOLLIN�¼���.
(������ʾ:�����������Կͻ���,����ر�����ʱ����ٴγ���IO�ɶ��¼�
��server,��ʱserver�ͻ�ȥ��ȡʣ�µ�5�ֽ�������,������һ�¼���ǰ����
����ET���ʲ���ì��.)
*/

/*client_send_sleep.pl*/
/*���Է���,��server������5�ֽڵ�����
֮��һֱ��������client���¼�,
����client����5��֮�����·�������,server�ٴμ������˱仯,
ֻ������Ϊֻ�Ƕ�ȡ��5���ֽ�,��Ȼ��10���ֽڵ�����
(client�ڶ��η��͵�����)û�н�����.*/

/*��������ʵ����,��accept��socket�����õ���LTģʽ,
��ôֻҪ������������buffer��,server�ͻ�����õ�֪ͨ,
���߿������иĶ��������ʵ��.
����������ʵ��,���Եó������Ľ���:ETģʽ����״̬�����仯��ʱ��Ż��֪ͨ,
������ν��״̬�ı仯���������������л���δ���������,Ҳ����˵,���Ҫ����ETģʽ,
��Ҫһֱread/writeֱ������Ϊֹ,�ܶ��˷�ӳΪʲô����ETģʽֻ������
һ�������ݾ���Ҳ�ò���֪ͨ��,�����Ϊ����;��LT
ģʽ��ֻҪ������û�д���ͻ�һֱ֪ͨ��ȥ��.
����˵��һ������һֱǿ����"״̬�仯"��ʲô:
1)���ڼ����ɶ��¼�ʱ,�����socket�Ǽ���socket,
��ô�����µ��������ӵ���Ϊ״̬�����仯;��һ���socket����,
Э��ջ����Ӧ�Ļ��������µ�����Ϊ״̬�����仯.����,
�����һ��ʱ��ͬʱ������N������(N>1),���Ǽ���socketֻaccept��һ������,
��ô����δ accept�����ӽ�������ETģʽ�¸�����socket����֪ͨ,��ʱ״̬�������仯;
����һ���socket,���������ж���,�����Ӧ�Ļ����������Ѿ�����N�ֽڵ�����,
��ֻȡ����С��N�ֽڵ�����,��ô�д�����ݲ������״̬�����仯.
2)���ڼ�����д�¼�ʱ,ͬ�����,��������.
�������Ǽ����ɶ����ǿ�д,�Է��ر�socket���Ӷ������״̬�����仯,
������������,���ǿ���ж�client�ű�,Ҳ���������ж���socket����,��ô
�������server�˷���״̬�ı仯,�Ӷ�server�õ�֪ͨ,���Ѿ��ڱ����������е����ݶ���.
��ǰ������������ܽ�����:�����Է��Ķ���(��������,�ر����ӵ�)
��ɵ��¼����ܵ���״̬�����仯,������Э��ջ���Ѿ�������¼�
(���������˶Է�������,�����˶Է���������������)���������״̬�����仯�ı�Ҫ����,
״̬�仯һ���ǶԷ���ɵ�.������ETģʽ�µ�,����һֱ�������������ȫ�������,
���ܽ�����һ������,������ܻᷢ������.
����,�����������,Ҳ���Բ���һЩ�����������̸���.
����,���ӵ�������,һ�˷��ͳɹ����������ŶԷ��ϲ�Ӧ�ó�����ճɹ�,
���������client���Գ�����˵,10�ֽڵ������Ѿ����ͳɹ�,
�����ϲ��server��û�е���read��ȡ����,��˷��ͳɹ�����˵�������ݱ��Է�
��Э��ջ���մ��������Ӧ��buffer��,���ϲ��Ӧ�ó����Ƿ�������ⲿ�����ݲ��ö�֪;
ͬ����,��ȡ����ʱҲֻ�����ű���Э��ջ�Ķ�Ӧ buffer�������ݿɶ�,
����ʱʱ���ڶԶ��Ƿ��ڷ�������Ҳ���ö�֪.
*/

