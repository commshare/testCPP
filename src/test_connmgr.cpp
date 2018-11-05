#include <iostream>
using namespace std;

typedef std::map<StatDimId, SdkDimCrossQuotaStat> DimId2SdkDimCrossQuotaStatMap;

struct SdkDimCrossQuotaStat
{
  uint64_t sendFlowTotal;
  uint64_t recvFlowTotal;
  uint64_t outSendTotal; //下行的发包数
  uint64_t outRecvTotal; //下行的收包数
  
  


}

struct StatDimId 
{
  StatDimId()
    : value(0)
  {
  	std::cout <<"StatDimId constructor" <<endl;
  }
   inline void setDimId(uint16_t svcId, uint16_t msgType, uint32_t appid)
  {
    value = ((uint64_t)svcId << 48) | ((uint64_t)msgType << 32) | ((uint64_t)appid);
    std::cout<<"value :"<<value<<endl;
  }
    inline bool operator == (const StatDimId& id) const
  {
    return value == id.value;
  }
  
  private:
  uint64_t value;
};
struct SdkQuotaStat
{
	 uint64_t linkSendFlow;
	 DimId2SdkDimCrossQuotaStatMap mapSdkDimCrossQuotaStat;

}


class ConnMgr{
	public:
		ConnMgr();
		~ConnMgr();
		
	    StatDimId m_statDimId; //用于流量维度统计

	    SdkQuotaStat m_sdkQuotaStat;
		public :
			int onData();

};

int ConnMgr::onData(){
 	m_statDimId.setDimId(INNER_SVCID, INNER_MESG_TYPE, INNER_APPID);
	SdkDimCrossQuotaStat &tmpStat = m_sdkQuotaStat.mapSdkDimCrossQuotaStat[m_statDimId];

	return 0;
}

