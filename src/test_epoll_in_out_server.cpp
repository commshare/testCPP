//https://blog.csdn.net/hintonic/article/details/16882989
//server.cpp

 

#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define MAXLINE 1024
#define SERV_PORT 8877

//���������������������������˳�
void error_quit(const char *str)    
{    
 perror(str);
 exit(1);    
}  

int main(void)      
{      
 int listenfd, connfd, sockfd, epfd;    
 int i, res, maxi, nfds;    
 ssize_t n = 10;      
 char buf[MAXLINE] = "world";      
 socklen_t clilen;      
 struct sockaddr_in cliaddr;      
 struct sockaddr_in servaddr;    

 //����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�      
 struct epoll_event ev, events[256];     

 //����һ��epoll�ľ����size���������ں������������Ŀһ���ж��      
 epfd = epoll_create(256);     
 if( -1 == epfd )
  error_quit("epoll_create error");

 //��������TCPЭ����׽���        
 listenfd = socket(AF_INET, SOCK_STREAM, 0);      
 memset(&servaddr, 0, sizeof(servaddr));      
 servaddr.sin_family = AF_INET;      
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);      
 servaddr.sin_port = htons(SERV_PORT);     

 //��socket��socket��ַ�ṹ��ϵ����       
 res = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));    
 if( -1 == res )
  error_quit("bind error");

 //��ʼ����LISTENQ�˿�       
 res = listen(listenfd, INADDR_ANY);    
 if( -1 == res )
  error_quit("listen error");

 //������Ҫ������¼���ص��ļ����������¼�    
 ev.data.fd = listenfd;      
 /*
 events���������¼�����ļ��ϣ�
 EPOLLIN ����ʾ��Ӧ���ļ����������Զ��������Զ�SOCKET�����رգ���
 EPOLLOUT����ʾ��Ӧ���ļ�����������д��
 EPOLLPRI����ʾ��Ӧ���ļ��������н��������ݿɶ�������Ӧ�ñ�ʾ�д������ݵ�������
 EPOLLERR����ʾ��Ӧ���ļ���������������
 EPOLLHUP����ʾ��Ӧ���ļ����������Ҷϣ�
 EPOLLET�� ��EPOLL��Ϊ��Ե����(Edge Triggered)ģʽ�����������ˮƽ����(Level Triggered)��˵�ġ�
 EPOLLONESHOT��ֻ����һ���¼���������������¼�֮���������Ҫ�����������socket�Ļ�����Ҫ�ٴΰ����socket���뵽EPOLL������
 */
 ev.events = EPOLLIN|EPOLLET;     

 //ע��epoll�¼�      
 epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd,&ev);      
 maxi = 0;   

 while(1)    
 {      
  //�ȴ�epoll�¼��ķ���      
  //������Ҫ������¼���Ŀnfds���緵��0��ʾ�ѳ�ʱ��      
  nfds = epoll_wait(epfd, events, 20, 500);     

  //�����������������¼�      
  for(i=0; i < nfds; ++i)      
  {      
   //����¼�⵽һ��SOCKET�û����ӵ��˰󶨵�SOCKET�˿ڣ������µ����ӡ�      
   if(events[i].data.fd == listenfd)      
   {      
    connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);  
    if( -1 == connfd )
     error_quit("accept error");   

    //ע�����ڶ��������ļ����������¼�    
    ev.data.fd = connfd;      
    ev.events =  EPOLLIN|EPOLLOUT|EPOLLET|EPOLLERR|EPOLLHUP;        
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);     
    if( -1 == res )
     error_quit("epoll_ctl error");
   }
   //��������ݷ���    
   else if(events[i].events & EPOLLOUT)     
   {    
    cout << "EPOLLOUT event"  << endl;
    sockfd = events[i].data.fd;    
    res = write(sockfd, buf, 10 ); 
    cout << "write " << res << " bytes. errno" << errno <<  ", str is "
     << strerror( errno ) << endl;
    //ע�����ڶ��������ļ����������¼�    
    /*ev.data.fd = sockfd;    
    ev.events = EPOLLIN|EPOLLET;    
    res = epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);    
    if( -1 == res )
     error_quit("epoll_ctl error");
     */
   }
   //������Ѿ����ӵ��û��������յ����ݣ���ô���ж��롣      
   else if(events[i].events & EPOLLIN)      
   {
    cout << "EPOLLIN event"  << endl;
    sockfd = events[i].data.fd;    
    if ( sockfd < 0 )      
     continue;      
    n = read(sockfd, buf, MAXLINE);    
    if ( n < 0)       
    {        
     // Connection Reset:�����ӵ���һ���Ѿ��Ͽ��ˣ�    
     //����ȴ�������ڶԷ��ѶϿ���socketfd�϶�д���ݣ�      
     if (errno == ECONNRESET)      
     {      
      close(sockfd);      
      events[i].data.fd = -1;      
     }       
     else      
      error_quit("read error");    
    }       
    //������������Ϊ��      
    else if ( n == 0 )     
    {      
     close(sockfd);      
     events[i].data.fd = -1;      
    }
    /*
    else    
    {    
     //ע������д�������ļ����������¼�    
     ev.data.fd = sockfd;    
     ev.events = EPOLLOUT|EPOLLET;     
     res = epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);    
     if( -1 == res )
      error_quit("epoll_ctl error");
    } 
    */    
        
   }    //��������ݷ���    
   else if(events[i].events & EPOLLERR)     
   {    
    cout << "EPOLLERR event"  << endl;
   }
   else if(events[i].events & EPOLLHUP)     
   {    
    cout << "EPOLLHUP event"  << endl;
   }
  }    
 }    
 return 0;      
}     

 
