 #include <stdint.h>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

struct StatDimId 
{
  StatDimId()
    : value(0)
  {
  }
  StatDimId(const StatDimId& id)
    : value(id.value)
  {
  }
  StatDimId(uint16_t svcId, uint16_t msgType, uint32_t appid)
  {
    value = ((uint64_t)svcId << 48) | ((uint64_t)msgType << 32) | ((uint64_t)appid);
  }
  StatDimId(uint64_t id)
    : value(id)
  {
  }

  const StatDimId& operator = (const StatDimId& id)
  {
    if (this != &id)
    {
      value = id.value;
    }
    return *this;
  }

  inline void setDimId(uint16_t svcId, uint16_t msgType, uint32_t appid)
  {
    value = ((uint64_t)svcId << 48) | ((uint64_t)msgType << 32) | ((uint64_t)appid);
  }
  inline bool operator == (const StatDimId& id) const
  {
    return value == id.value;
  }

  inline bool operator < (const StatDimId& id) const
  {
    return value < id.value;
  }
  inline bool operator < (uint64_t id) const
  {
    return value < id;
  }
  inline uint16_t getSvcId() const
  {
    return uint16_t(value >> 48);
  }
  inline uint16_t getMsgType() const
  {
    return uint16_t((value & 0x0000ffff00000000) >> 32);
  }
  inline uint32_t getAppId() const
  {
    return uint32_t(value & 0x00000000ffffffff);
  }
  inline uint64_t getHashValue() const
  {
    return value;
  }
  inline uint64_t get64Value() const
  {
    return value;  
  }
private:
  uint64_t value;
};

int main(){
	uint16_t svcId = 0;
	uint16_t msgType = 0 ; 
	uint32_t appid = 0xffffffff;
	StatDimId id ;
	id.setDimId(svcId,msgType,appid);
	cout <<"dimid "<<id.get64Value() <<endl;
	cout <<"appid "<<id.getAppId() <<endl;
	cout <<"hash "<<id.getHashValue()<<endl;
	cout <<"msgid "<<id.getMsgType() <<endl;
	cout <<"svcid "<<id.getSvcId() <<endl;
	
	uint32_t     newappid 	= 0xffffffff & id.get64Value();
  //svcid = uint16_t(it->first >> 48);
 // msgId = uint16_t((it->first >> 32) & 0xFFFF);
    //msgId &= 0xFF;

    if(0xFFFFFFFF == newappid)
    {
      cout <<" not like 0xffffffff appid " <<endl;
    }else{
    	cout <<" ok ,valid appid " <<endl;
	}
	return 0;
}
/*
dimid 4294967295
appid 4294967295
hash 4294967295
msgid 0
svcid 0
*/


