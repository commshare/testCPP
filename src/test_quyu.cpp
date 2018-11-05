#include <iostream>
 #include <stdint.h>

using namespace std;


//bussData.seq % (getDelayStatCalcStep()*PACKET_SEQ_INCREMENT) == 0

uint32_t cal( uint32_t seq,uint32_t step){
	uint32_t v = step;
	if (step == 0 ){
		v= 0xFFFFFFFF;
	}
	uint32_t out = seq % (v *2 );
	return out;
}

int main(){
	  uint32_t seq; 
	  seq = 0;
	  std::cout <<"cal " <<seq << cal(seq,0) <<endl;
	  seq =2;
	  	  std::cout <<"cal " <<seq <<" :"<< cal(seq,0) <<endl;
	  seq = 100;
	  	  std::cout <<"cal " <<seq <<" :"<< cal(seq,0) <<endl;
	  	  seq = 89900;
	  	  std::cout <<"cal " <<seq <<" :"<< cal(seq,0) <<endl;
	  seq = 3000000;
	  	  std::cout <<"cal " <<seq <<" :"<< cal(seq,0) <<endl;
	  seq = 0xFFFFFFFF;
	  	  std::cout <<"cal " <<seq << " :"<<cal(seq,0) <<endl;	  
} 
