#include<stdio.h>
#include<stdlib.h>

/*�����ܷ�ı��ⲿ��pHeader2*/
#define TEST_CHANGE_pHeader2 0


/*��һ��С��ģʽ�Ļ������ȡһ���ֽڡ������ֽ�*/
/*��С��ģʽ��buf���ȡ�ֽڣ����մ��ģʽ����

���ģʽ������1024�ɣ��ȷ�1���ٷ�0���͵�ַ���ڴ��ŵ��Ǹ�λ����
С��ģʽ�����ǵ͵�ַ���ڴ棬��ŵľ��ǵ�λ���飬1024���ȴ��4.
*/
int bytestream_get_byte(const unsigned char ** buf){
		 unsigned char *p=*buf;
   printf("*buf [%c]\n   [%d] \n [%d]\n",*p,*p,(*p)&&0x000000FF);
return (int)(*p);

}

/*buf��С�ˣ��͵�ַ���ǵ�λ����*/
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


/*buf�Ǵ�ˣ����ص�Ҳ�Ǵ��,�ҿ��Ըı�ָ�����*/ 
int bytestream2_get_byte(const unsigned char ** buf){
		 unsigned char *p=*buf;
   printf("*buf [%c]\n   [%d] \n [%d]\n",*p,*p,(*p)&&0x000000FF);
      
int a= (int)(*p);
  printf("#1#move to next \n");
  
  #if TEST_CHANGE_pHeader2
  p=p+1; /*�����ã��ı����p,���ı��ⲿ��pHeader2*/ 
   printf("(*p)[%d]\n",*p);
  #else  
   p=p+1;
 (*buf)=(*buf)+1;
 //buf=buf+1;
 
 printf("(*p)[%d] *(*buf )[%d]\n",*p,*(*buf));
 #endif
 return a;
}
/*�����ˣ����Ҳ��ˣ��ҿ��Ըı�ָ�����*/
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
	 p=p+3;/*�����ã��ı����p,����ı��ⲿ��pHeader2*/ 
	 printf("(*p)[%d]\n",*p);
	 #else
//	buf=buf+1;  /*�����ã��ı����buf*/
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