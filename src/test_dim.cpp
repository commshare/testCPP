 #include <stdint.h>
#include <iostream>
#include <sstream>
using namespace std;

uint64_t genAppid(uint32_t delaytype ,uint32_t appid ){
	return  ((uint64_t)delaytype << 32) | ((uint64_t)appid);
}
uint64_t get16Sid(uint32_t delaytype ,uint16_t  svcid){
	return  ((uint64_t)delaytype << 32)  | ((uint64_t)svcid);
}
uint64_t get8Tid(uint32_t delaytype,uint8_t ssid){
	return  ((uint64_t)delaytype << 32)  | ((uint64_t)ssid);
}

/*
    appid = 0xffffffff & it->first;
    svcid = uint16_t(it->first >> 48);
    msgId = uint16_t((it->first >> 32) & 0xFFFF);
*/

typedef struct Result{
    int shang;
    int yu;
}Result;
bool checkUint64(uint64_t id ,uint32_t &appid,uint16_t &sid , uint8_t &tid){
       bool ret = true ;

	uint32_t type =  uint32_t(id>>32) ;
	switch(type){
		case  0 : {
			cout <<" type appid " <<endl;
		    appid = 0xffffffff & id;
		}
		break;
		case 1 : {
		
			sid = uint16_t(0xffff & id);	
				cout <<"type 16 sid" <<sid <<endl; 
			break;
		}
		
		case 2:
			{
				tid = uint8_t(0xff & id);
				cout <<"type 8 tid " <<endl;
				
				break; 
			}	 
		default :{
			cout <<"unkown "<<type << endl;
			ret = false;
			break;
		}
			
			}
	return ret;
	}


int main(){
	uint8_t  tid = 0;
	uint16_t sid = 47677;  //65535
	uint32_t appid = 88766;
	
	uint64_t a = genAppid(0,appid);
	uint64_t b = get16Sid(1,sid);
	uint64_t c = get8Tid(2,tid);
	
	uint64_t d= 12884901888;
	std::cout<<"a :"<<a <<std::dec <<" Hex:"<< hex << uppercase <<a<<std::dec<<endl; 
	  std::cout<<"b :"<<b <<std::dec <<" Hex:"<< hex << uppercase <<b<<std::dec<<endl; 
	    std::cout<<"c :"<<c <<std::dec <<" Hex:"<< hex << uppercase <<c<<std::dec<<endl; 
	    
	    uint32_t type ;
	    uint64_t id =d;
	    cout <<" tid "<<(unsigned )tid <<endl; 
	    std::cout<<"id :"<<id <<std::dec <<" Hex:"<< hex << uppercase <<id<<std::dec<<endl; 
	    bool ret =  checkUint64(id ,appid ,sid,tid );
	    
	    cout<<" id :"<<id <<" appid "<<appid <<" sid "<<sid <<" tid "<<(unsigned)tid <<"ret "<< ret <<endl;
	    cout <<"40"<<" /"<<"50"<<endl;
	return 0;
}

/*
a :255 Hex:FF
b :4294967551 Hex:1000000FF
c :8589934847 Hex:2000000FF

*/ 
