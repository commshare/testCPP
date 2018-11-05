#include <iostream>
#include <ctype.h>
 #include <stdint.h>
#include <time.h> 

using namespace std;
 // uint16_t mesgType;          //��Ϣ���ͣ�[0,2]:�������� [3,4]:�������ȼ� [5,6]:ϵͳ���� [7,7]:�ಥ�򵥲���0�ಥ,1����)

enum MSG_TYPE_FLAG  //���Ǹ�����һ���ֽ�
{
  MSG_TYPE_DATA_TYPE_MASK      = 0x0007,
  MSG_TYPE_PRIORITY_MASK      = (0x0003 << 3),
  MSG_TYPE_SYS_TYPE_MASK      = (0x0003 << 5),
  MSG_TYPE_MULTICAST_TYPE_MASK = (0x0001 << 7),
};
#define GET_MSGTYPE_DATATYPE_VALUE(msgtype) (uint8_t(msgtype & MSG_TYPE_DATA_TYPE_MASK))
#define GET_MSGTYPE_PRIORITY_VALUE(msgtype) (uint8_t((msgtype & MSG_TYPE_PRIORITY_MASK ) >> 3))
#define GET_MSGTYPE_SYSTYPE_VALUE(msgtype) (uint8_t((msgtype & MSG_TYPE_SYS_TYPE_MASK ) >> 5))
#define GET_MSGTYPE_MULTICAST_VALUE(msgtype) (uintmesgType8_t((msgtype & MSG_TYPE_MULTICAST_TYPE_MASK ) >> 7))

//����ķ���ֵ now :1525250827801365 
  //��ȡ��ǰ��ʵʱʱ�䣬��ȷ��΢�롣
  //ͨ����������ʱ��ʱ�䣬���ϻ������е�ʱ��ķ�ʽ��ȡ��
  //��Ϊclock_gettime���Ի�ȡ��������ϵͳʱ��Ļ�������ʱ�䣬
  //���Կ��Ա�����Ϊ������Ա����ϵͳʱ�������ʱ��Ķ�����
  inline uint64_t get_real_clocktime()
  {
    static uint64_t s_rebootTime = 0;
    struct timespec machineRunTime;
    const uint32_t ONE_SECOND_TO_US = 1000*1000; //1 second = 1000000 us

    if(s_rebootTime == 0) {
      struct timespec realTime;
      int ret1 = clock_gettime(CLOCK_MONOTONIC, &machineRunTime);
      int ret2 = clock_gettime(CLOCK_REALTIME, &realTime);
      if(ret1 != 0 || ret2 != 0)
        return 0;

      uint64_t iRealTime = realTime.tv_sec * ONE_SECOND_TO_US + (realTime.tv_nsec / 1000);
      uint64_t iRunTime = machineRunTime.tv_sec * ONE_SECOND_TO_US + (machineRunTime.tv_nsec / 1000);
      s_rebootTime = iRealTime - iRunTime ;
      return iRealTime;
    }

    //��ȡ�����ϴ�������ʱ����������ϵͳʱ����Ӱ��
    if(clock_gettime(CLOCK_MONOTONIC, &machineRunTime) != 0)
      return 0;

    uint64_t iRunTime = machineRunTime.tv_sec * ONE_SECOND_TO_US + (machineRunTime.tv_nsec / 1000);
    return (s_rebootTime + iRunTime);
  }
  
  /*���Ͷ�*/ 
  //[0,61]��timestamp  [62,63]��index 
  //  inline uint64_t sendMsgType(uint8_t index, uint64_t timestamp)
 // {
 //   return (((uint16_t)brocastType << 7) | ((uint16_t)sysType << 5) | ((uint16_t)priority << 3) | dataType);
 // }
 
int main(){
		
	uint32_t index =2 ;
	 std::cout<<"index :"<<index  <<endl; 
	
	uint64_t timeIn64Bit = get_real_clocktime();
	// now :1525250827801365 
	std::cout<<"now :"<<timeIn64Bit <<" Hex:"<< hex << uppercase << timeIn64Bit <<std::dec <<endl;

	/*��Ҫ������62λ�����ݣ�ǿ��תΪint64λ֮���������ƣ���û�о�����
	test_timestamp.cp:66:47: warning: left shift count >= width of type [-Wshift-count-overflow]
  uint64_t first = (uint64_t)((index & 0x03) <<62) ;
                                               ^

	*/
	uint64_t first = ((uint64_t)(index & 0x00000003) <<62) ;
	 std::cout<<"first :"<<first <<std::dec <<" Hex:"<< hex << uppercase <<first<<std::dec <<endl;
	uint64_t second =  (timeIn64Bit & 0x3FFFFFFFFFFFFFFF) ;
	 	 std::cout<<"second :"<<second <<std::dec <<" Hex:"<< hex << uppercase <<second <<endl;
	uint64_t timestamp = first |  (timeIn64Bit & 0x3FFFFFFFFFFFFFFF) ;
	 std::cout<<"merge :"<<timestamp <<std::dec;
	 std::cout <<" Hex:"<< hex << uppercase <<timestamp<<endl;
	
	uint64_t last =  ((uint64_t)(index & 0x00000003) <<62)    |  (timeIn64Bit & 0x3FFFFFFFFFFFFFFF)  ; 
		 std::cout<<"last :"<<last <<std::dec <<" Hex:"<< hex << uppercase <<last<<std::dec<<endl;
		 
		 
		             /*Ҫ��timestamp������stampc��index*/
            uint32_t indexR = uint32_t((last & 0xC000000000000000) >> 62);
            //����ֱ������62λ��ok��
			uint32_t indexR1 = uint32_t(last>> 62); 
            uint64_t realts = (last & 0X3FFFFFFFFFFFFFFF);
            std::cout<<"indexR :"<<indexR <<std::dec <<" Hex:"<< hex << uppercase <<indexR<<std::dec<<endl;
            std::cout<<"indexR1 :"<<indexR1 <<std::dec <<" Hex:"<< hex << uppercase <<indexR1<<std::dec<<endl;
            std::cout<<"realts :"<<realts <<std::dec <<" Hex:"<< hex << uppercase <<realts<<std::dec<<endl;

	uint32_t last32 = (uint32_t)last;
	 std::cout<<"last32 :"<<last32 <<std::dec <<" Hex:"<< hex << uppercase <<last32<<std::dec<<endl;
    std::cout<<"last :"<<last <<std::dec <<" Hex:"<< hex << uppercase <<last<<std::dec<<endl; 
    
      uint64_t extFlag = 0;
      uint64_t e1 = extFlag | (0X0000000000000001 << 16) -1;
       extFlag = 0;
      uint64_t e2 = extFlag | (0X0000000000000001 << 15);
      /*
	  e1 :65535 Hex:FFFF
e2 :65535 Hex:8000
	  */

        std::cout<<"e1 :"<<e1 <<std::dec <<" Hex:"<< hex << uppercase <<e1<<std::dec<<endl; 
        std::cout<<"e2 :"<<e1 <<std::dec <<" Hex:"<< hex << uppercase <<e2<<std::dec<<endl; 
        	         extFlag = 0;
      uint64_t e3 = extFlag | (0X0000000000000001 << 16);
      	         extFlag = 0;
      uint64_t e4 = extFlag | (0X0000000000000001 << 17)-1;
        std::cout<<"e3 :"<<e1 <<std::dec <<" Hex:"<< hex << uppercase <<e3<<std::dec<<endl; 
        std::cout<<"e4 :"<<e1 <<std::dec <<" Hex:"<< hex << uppercase <<e4<<std::dec<<endl; 
}  
/*
ע�⣺
    uint64_t timestamp =  (uint64_t) ( (index & 0x00000003) <<62)    |  (ts.stampc & 0x3FFFFFFFFFFFFFFF)  ;

���������Ǵ���ġ� 
@@send-1-now :1525405252184480 Hex:56B591631E9A0
@@@-2- index :2 Hex:2
@@@-3-timestamp :1525405252184480 last 9224897442106960288 Hex:56B591631E9A0 Hex:80056B591631E9A0

���Կ�����last�ǶԵģ�timestamp��������now��һ��ֵ�� 
*/
/*
root@ubuntu:/home/zhangbin/ffmpeg/RECORD_TEST/testCPP/src# ./test_timestampindex :
now :1525252122023605 Hex:56B356EED16B5
first :9223372036854775808 Hex:8000000000000000
merge :9224897288976799413 Hex:80056B356EED16B5
root@ubuntu:/home/zhangbin/ffmpeg/RECORD_TEST/testCPP/src# 


*/

/*
int64_t GmSdkManager::genTimestamp() {
    int32_t index = -1;
    int64_t now = getGmTime(index);
    uint64_t result =  ((uint64_t)(index & 0x00000003) <<62)    |  (now & 0x3FFFFFFFFFFFFFFF)  ;
    return result;
}


*/ 
/*
ǿתΪ32λ
last32 :735415477 Hex:2BD58CB5
last :9224897524074384565 Hex:80056B6C2BD58CB5
 
*/
