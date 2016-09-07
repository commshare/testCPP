#include<stdio.h>
#include<stdlib.h>

/*测试能否改变外部的pHeader2*/
#define TEST_CHANGE_pHeader2 0


/*从一个小端模式的缓冲里读取一个字节、三个字节*/
/*从小端模式的buf里读取字节，按照大端模式发送

大端模式，就是1024吧，先发1，再发0，低地址的内存存放的是高位数字
小端模式，就是低地址的内存，存放的就是低位数组，1024，先存放4.
*/
int bytestream_get_byte(const unsigned char ** buf){
		 unsigned char *p=*buf;
   printf("*buf [%c]\n   [%d] \n [%d]\n",*p,*p,(*p)&&0x000000FF);
return (int)(*p);

}

/*buf是小端，低地址就是低位数字*/
int bytestream_get_be24(const unsigned char ** buf){
	 unsigned char *p=*buf;
     unsigned char a=(*p);
     unsigned char b=(*(p+1));
     unsigned char c=(*(p+2));
   // int d=(c<<3)&&0x0000FFFF0000||(b<<2)&&0x00000000FFFF0000||a&&0x000000FF;
   int d=(c<<16) | (b<<8) | (c) ;
	printf("a[%d] \n b[%d] \nc[%d] \n d[%d]\n",a,b,c,d);
     return d;
}


/*buf是大端，返回的也是大端,且可以改变指针后移*/ 
int bytestream2_get_byte(const unsigned char ** buf){
		 unsigned char *p=*buf;
   printf("*buf [%c]\n   [%d] \n [%d]\n",*p,*p,(*p)&&0x000000FF);
      
int a= (int)(*p);
  printf("#1#move to next \n");
  
  #if TEST_CHANGE_pHeader2
  p=p+1; /*不管用，改变的是p,不改变外部的pHeader2*/ 
   printf("(*p)[%d]\n",*p);
  #else  
   p=p+1;
 (*buf)=(*buf)+1;
 //buf=buf+1;
 
 printf("(*p)[%d] *(*buf )[%d]\n",*p,*(*buf));
 #endif
 return a;
}
/*输入大端，输出也大端，且可以改变指针后移*/
int bytestream2_get_be24(const unsigned char ** buf){
	 unsigned char *p=*buf;
     unsigned char a=(*p);
     unsigned char b=(*(p+1));
     unsigned char c=(*(p+2));
   // int d=(c<<3)&&0x0000FFFF0000||(b<<2)&&0x00000000FFFF0000||a&&0x000000FF;
   int d=(c<<16) | (b<<8) | (c) ;
	printf("a[%d] \n b[%d] \nc[%d] \n d[%d]\n",a,b,c,d);
	 printf("#2#move to next \n");
	 #if TEST_CHANGE_pHeader2
	 p=p+3;/*不管用，改变的是p,不会改变外部的pHeader2*/ 
	 printf("(*p)[%d]\n",*p);
	 #else
//	buf=buf+1;  /*不管用，改变的是buf*/
 p=p+3;
(*buf)=(*buf)+3;

	 printf("(*p)[%d] **buf [%d]\n",*p,**buf);
	 #endif
     return d;
}

void main(){
	char buf[10]={0};
	int i;
	for(i=0;i<10;i++){
		buf[i]=i+1;
	}
	for(i=0;i<10;i++){
		printf("buf[%d]\n",buf[i]);
	}
		 unsigned char *pHeader = buf;
		 unsigned char *pHeader2 = buf;

	 int pktSize, pktType;
	  pktType = bytestream_get_byte((const unsigned char **) &pHeader);
	  printf("pktType[%d]\n",pktType);
    pktSize = bytestream_get_be24((const unsigned char **) &pHeader);
    printf("pktSize[%d]\n",pktSize);
    printf("##########################################\n");
    int size=bytestream2_get_byte((const unsigned char **) &pHeader2);
    int type=bytestream2_get_be24((const unsigned char **) &pHeader2);
    printf("size[%d] type[%d] (*pHeader2)[%d]\n",size,type,*pHeader2);
	system("pause");
	return;
}
