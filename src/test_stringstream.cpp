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
 
    //单播数据将对端sdkid作为多播组id创建dq
    std::stringstream os(name);
    os >> sdkId;
    
    cout<<"sdkid "<<sdkId<<endl;
      cout<<"name "<<name<<endl;
      cout<<"os "<<os <<endl;
} 
  

