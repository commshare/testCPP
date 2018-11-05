#include <iostream>
#include <ctype.h>
 #include <stdint.h>
#include <time.h> 
using namespace std; 

#define PACKET_DELAY_CACSTEP (7) /*a step to calculate packet delay time */


void ClogBussData(std::string& params)
{
  uint32_t uiEnable = 0;
  cout << "before: " <<uiEnable <<endl;
  if (sscanf(params.c_str(), "%u", &uiEnable) == 1)
  {
    bool bEnable = (bool)uiEnable;
   
    cout << ", after: " << uiEnable <<"bEnable :"<<bEnable<<endl;
  }
  cout << std::endl;

}
int main(){
	for(int i=0;i<200;i=i+2)
	{
		if (i % (PACKET_DELAY_CACSTEP*2) == 0 ) {
			cout<< i << endl;
		}
	}
	std::string param = "-0";
	ClogBussData(param);
	return 0;
}
