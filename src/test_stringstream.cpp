  #include<iostream>  
#include<set>  
#include<algorithm>  
 #include <stdint.h>
#include<vector>  
#include <sstream> // for istringstream 


using namespace std;  


int main()
{
	  uint64_t sdkId = 199;
    std::string name = "zhangbin";
 
    //�������ݽ��Զ�sdkid��Ϊ�ಥ��id����dq
    std::stringstream os(name);
    os >> sdkId;
    
    cout<<"sdkid "<<sdkId<<endl;
      cout<<"name "<<name<<endl;
      cout<<"os "<<os <<endl;
} 
  

