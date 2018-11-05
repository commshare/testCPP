#include <iostream>
#include <ctype.h>
 #include <stdint.h>
#include <time.h> 
using namespace std; 

#define PACKET_DELAY_CACSTEP 6
int getvalue(int &v){
	v= 256;
	cout<<"getvalue set v ref to "<<v <<endl;
	return 0;
}

int getv(){
	int v = -1;
	cout<<"getv set v to "<<v <<endl;
	getvalue(v);
	return v;
}
/*最多支持到255，-1会输出255，0会输出0,大于255输入会出错，256也得到0*/ 
uint8_t getVUint8(){
	int v = -1;
	cout<<"getVUint8 set v to "<<v <<endl;
	getvalue(v);
	return (uint8_t)v;
}
void getTime(int &tmp){
	tmp = 10;
}
void gents(int i){
	getTime(i);
	cout<<"i "<<i<<endl;  //还是被修改为10了 
}
void gents2(int i){
	i = -1; 
	getTime(i);
	cout<<"i "<<i<<endl;  //还是被修改为10了 
}
int main(){
	int v = getv();
	cout <<"v = "<<v<<endl;
	uint8_t v8 = getVUint8();
	cout <<"v8 = "<<(unsigned)v8<<endl;
	
	for(int i= 0 ;i< 100 ;i=i+2){
		if( i %  (2* PACKET_DELAY_CACSTEP ) ==0 ){
			cout<<"----- 10 : i " <<i <<endl;;
		}else{
			cout<<"not 10 : i " <<i <<endl;;
		}
	}
	uint8_t a= 5;
	uint32_t b= (uint32_t)a;
	cout<<"b "<<b<<endl;
	uint16_t c= 188;
	uint32_t d = (uint32_t)c;
	cout<<"c "<<d<<endl;
	   std::cout<<"a :"<<a <<std::dec <<" Hex:"<< hex << uppercase <<a<<std::dec<<endl; 
	   	   std::cout<<"b :"<<b <<std::dec <<" Hex:"<< hex << uppercase <<b<<std::dec<<endl; 
	   	   	   std::cout<<"c :"<<c <<std::dec <<" Hex:"<< hex << uppercase <<c<<std::dec<<endl; 
	   	   	   	   std::cout<<"d :"<<d <<std::dec <<" Hex:"<< hex << uppercase <<d<<std::dec<<endl; 

	b=100;
	d= 230;
	uint32_t e = b-d;
	int f =b -d ;
	cout<<"e "<<e<<" f "<<f<<endl;
	int index = 50;
	gents(index); //不是穿引用，所以这里打印到index还是50 
	cout <<"index "<<index<<endl;
	gents2(index);
	cout<<"index "<<index <<endl;
	return 0;
}


