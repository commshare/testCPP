#include<stdio.h>
#include<stdlib.h>


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
	 int pktSize, pktType;
	  pktType = bytestream_get_byte((const unsigned char **) &pHeader);
	  printf("pktType[%d]\n",pktType);
    pktSize = bytestream_get_be24((const unsigned char **) &pHeader);
    printf("pktSize[%d]\n",pktSize);
	system("pause");
	return;
}
