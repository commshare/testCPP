//https://blog.csdn.net/hintonic/article/details/16882989

//client.cpp

 

 #include <stdio.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>

using namespace std;

int main ( int argc, char ** argv )
{

 if ( argc < 5  )
 {
  cout << "Usage : ip port  kind need_crlf  str, like : 172.27.201.182 39752 tcp Y   hello"  << endl;

  return -1;

 }
 int iRet = -1;
 string sHost = argv[1];

 int iPort = atoi( argv[2] );

 string sKind = argv[3];
 string sNeedCRLF = argv[4];
 string  sIn  = argv[5];
 
 int sock_fd = -1, serverlen;
 struct sockaddr_in server_addr;

 if ( sKind == "udp" )
 { 
  sock_fd = socket( AF_INET, SOCK_DGRAM, 0 );
 }
 else if ( sKind == "tcp" )
 {
  sock_fd = socket( AF_INET, SOCK_STREAM, 0 );
 }
 
 if ( sock_fd == -1 )
 {

  cout <<  "create socket failed !!" << endl;

  return -1;

 }

 bzero( &server_addr, sizeof ( struct sockaddr_in ) );

 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons( iPort );
 server_addr.sin_addr.s_addr = inet_addr( sHost.c_str() );

 serverlen = sizeof ( server_addr );

 
 if ( sNeedCRLF == "Y"  )
 {
  sIn = sIn + "\r\n";
 }
 int iLen = sIn.length() ;
 if ( sKind == "tcp" )
 {
  iRet = connect( sock_fd, (struct sockaddr *)&server_addr, serverlen );
  if ( iRet != 0 )
  {
   cout << "connect failed"  << endl;
   return -1;
  }
 }
 cout <<  "connect to server " << sHost << ":" << iPort << endl;
 sleep( 10 );
 
 if  ( sendto( sock_fd, sIn.c_str(), iLen, 0, (struct sockaddr *)&server_addr, serverlen ) < 0)
 {

  cout <<  "send to server failed !!" << endl;

  close( sock_fd );

  return -2;
 }
 cout <<  "send to server " << sHost << ":" << iPort << endl;
 char sBuffer[1024] ;
 sleep( 10 );
 int iSize = ::recvfrom( sock_fd, sBuffer, 1024 , 0, 
  (struct sockaddr*)&server_addr, (socklen_t*)&serverlen);
 cout << "recv return: " << iSize << " bytes " << endl;
 cout << sBuffer << endl;
 sleep( 10 );
 close( sock_fd );

 cout <<  " send finished, close socket. " << endl;

 return 0;

}
