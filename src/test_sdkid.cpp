#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
 #include <stdint.h>
/*
uint64_t genSdkNodeId(uint32_t ip, uint16_t port)
{
  uint64_t sdkNodeId  = (((uint64_t)ip << 32) & 0xFFFFFFFF00000000LL)
    | ((m_nPid << 16) & 0x00000000FFFF0000LL)
    | (port & 0x000000000000FFFFLL);

 // LOG(Info, "genSdkNodeId, ip:%s, port:%u, pid:%u, snId: %lu", ip2str(ip), port, m_nPid, sdkNodeId);
  return sdkNodeId;
}
*/
/** 
 * ÕûÐÎ×ªip×Ö·û´® 
 */  


char *ip2str(uint32_t ip)
{
  union ip_addr{
    uint32_t addr;
    uint8_t s[4];
  } a;
  a.addr = ip;
  static char s[16];
  sprintf(s, "%u.%u.%u.%u", a.s[0], a.s[1], a.s[2], a.s[3]);
  return s;
}


void gen(uint64_t sdkNodeId){
	uint32_t  tt=  (uint32_t) (sdkNodeId >> 32 );
		printf("tt %lu ipstr %s \n",tt,ip2str(tt)); 
	uint64_t dd =uint64_t (sdkNodeId & 0xFFFFFFFF00000000LL );
		printf("dd %llu \n",dd); 
	uint32_t ip = uint32_t (dd >> 32) ;
	printf("ip %lu\n",ip); 
	
	uint16_t port =uint16_t (sdkNodeId & 0x000000000000FFFFLL );
	printf("port %d",port);
	
}

int main(){
  uint64_t id=	2815867028065428166;
 // id = 2356957223612129977;
   gen(id);
   return 0;
}
