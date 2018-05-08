 #include <stdint.h>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

//[0,30) [30,50) [50,80) [80,120) [120,200) >=200
enum TimeCostDistri
{
  TIME_DELAY_0_30,
  TIME_DELAY_30_50,
  TIME_DELAY_50_80,
  TIME_DELAY_80_120,
  TIME_DELAY_120_200,
  TIME_DELAY_200_MORE,
  TIME_DELAY_END,
};

enum TimeCostDistriUs
{
  TIME_DELAY_MS_0_30 = 30,
  TIME_DELAY_MS_30_50 = 50,
  TIME_DELAY_MS_50_80 = 80,
  TIME_DELAY_MS_80_120 = 120,
  TIME_DELAY_MS_120_200 = 200,
};


struct TimeDelay 
{
  uint64_t minCost;
  uint64_t maxCost;
  uint64_t totalCost;
  uint64_t count;
  uint32_t distri[TIME_DELAY_END];
  TimeDelay()
  {
    reinit();
  }
  void reinit()
  {
    minCost = 0XFFFFFFFFFFFFFFFF;
    maxCost = 0;
    totalCost= 0;
    count = 0;
    memset(distri, 0, sizeof(distri));
  }
  void Update(uint64_t timeCost)
  {
    if (timeCost < TIME_DELAY_MS_0_30)
    {
      ++distri[TIME_DELAY_0_30];
      return;
    }
    if (timeCost < TIME_DELAY_MS_30_50)
    {
      ++distri[TIME_DELAY_30_50];
      return;
    }
    if (timeCost < TIME_DELAY_MS_50_80)
    {
      ++distri[TIME_DELAY_50_80];
      return;
    }
    if (timeCost < TIME_DELAY_MS_80_120)
    {
      ++distri[TIME_DELAY_80_120];
      return;
    }  
    if (timeCost < TIME_DELAY_MS_120_200)
    {
    //	cout << "120_200 "<<timeCost <<endl;
      ++distri[TIME_DELAY_120_200];
      return;
    }
    //cout << "200 more :"<<timeCost <<endl;
    ++distri[TIME_DELAY_200_MORE];
  }
  	string getStatStr() { 
		ostringstream os;
		for(int i=0;i<TIME_DELAY_END;i++)
		{
			os<< distri[i] <<" ";
		}
		return os.str() ;// .c_str()
	 }
	void clearStat(){
	 memset(distri, 0, sizeof(distri));
	} 
};


int main(){
	TimeDelay st;
	//[0,30) [30,50) [50,80) [80,120) [120,200) >=200
	st.Update(20);
	st.Update(40);
	st.Update(60);
	st.Update(100);
	st.Update(190);
	st.Update(220);
	std::cout <<"stat: "<< st.getStatStr()<<endl;

	st.clearStat();
	for(int i=0;i<300;i++){
		st.Update(i);
	}
	std::cout <<"stat: "<< st.getStatStr()<<endl;

}

