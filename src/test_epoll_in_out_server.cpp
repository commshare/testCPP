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

//发生了致命错误，输出错误后立即退出
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

 //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件      
 struct epoll_event ev, events[256];     

 //创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大      
 epfd = epoll_create(256);     
 if( -1 == epfd )
  error_quit("epoll_create error");

 //创建用于TCP协议的套接字        
 listenfd = socket(AF_INET, SOCK_STREAM, 0);      
 memset(&servaddr, 0, sizeof(servaddr));      
 servaddr.sin_family = AF_INET;      
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);      
 servaddr.sin_port = htons(SERV_PORT);     

 //把socket和socket地址结构联系起来       
 res = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));    
 if( -1 == res )
  error_quit("bind error");

 //开始监听LISTENQ端口       
 res = listen(listenfd, INADDR_ANY);    
 if( -1 == res )
  error_quit("listen error");

 //设置与要处理的事件相关的文件描述符和事件    
 ev.data.fd = listenfd;      
 /*
 events可以是以下几个宏的集合：
 EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
 EPOLLOUT：表示对应的文件描述符可以写；
 EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
 EPOLLERR：表示对应的文件描述符发生错误；
 EPOLLHUP：表示对应的文件描述符被挂断；
 EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
 EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
 */
 ev.events = EPOLLIN|EPOLLET;     

 //注册epoll事件      
 epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd,&ev);      
 maxi = 0;   

 while(1)    
 {      
  //等待epoll事件的发生      
  //返回需要处理的事件数目nfds，如返回0表示已超时。      
  nfds = epoll_wait(epfd, events, 20, 500);     

  //处理所发生的所有事件      
  for(i=0; i < nfds; ++i)      
  {      
   //如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。      
   if(events[i].data.fd == listenfd)      
   {      
    connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);  
    if( -1 == connfd )
     error_quit("accept error");   

    //注册用于读操作的文件描述符和事件    
    ev.data.fd = connfd;      
    ev.events =  EPOLLIN|EPOLLOUT|EPOLLET|EPOLLERR|EPOLLHUP;        
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);     
    if( -1 == res )
     error_quit("epoll_ctl error");
   }
   //如果有数据发送    
   else if(events[i].events & EPOLLOUT)     
   {    
    cout << "EPOLLOUT event"  << endl;
    sockfd = events[i].data.fd;    
    res = write(sockfd, buf, 10 ); 
    cout << "write " << res << " bytes. errno" << errno <<  ", str is "
     << strerror( errno ) << endl;
    //注册用于读操作的文件描述符和事件    
    /*ev.data.fd = sockfd;    
    ev.events = EPOLLIN|EPOLLET;    
    res = epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);    
    if( -1 == res )
     error_quit("epoll_ctl error");
     */
   }
   //如果是已经连接的用户，并且收到数据，那么进行读入。      
   else if(events[i].events & EPOLLIN)      
   {
    cout << "EPOLLIN event"  << endl;
    sockfd = events[i].data.fd;    
    if ( sockfd < 0 )      
     continue;      
    n = read(sockfd, buf, MAXLINE);    
    if ( n < 0)       
    {        
     // Connection Reset:你连接的那一端已经断开了，    
     //而你却还试着在对方已断开的socketfd上读写数据！      
     if (errno == ECONNRESET)      
     {      
      close(sockfd);      
      events[i].data.fd = -1;      
     }       
     else      
      error_quit("read error");    
    }       
    //如果读入的数据为空      
    else if ( n == 0 )     
    {      
     close(sockfd);      
     events[i].data.fd = -1;      
    }
    /*
    else    
    {    
     //注册用于写操作的文件描述符和事件    
     ev.data.fd = sockfd;    
     ev.events = EPOLLOUT|EPOLLET;     
     res = epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);    
     if( -1 == res )
      error_quit("epoll_ctl error");
    } 
    */    
        
   }    //如果有数据发送    
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

 
