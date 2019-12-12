#include <iostream>

#include <string>
  struct UdbLoginSucParams
  {
  	UdbLoginSucParams()
  	{
	  }
  	UdbLoginSucParams( UdbLoginSucParams &p)
  	{	  
  	isRelogin_ = p.isRelogin_;
	  }
	bool isRelogin_;
  };
  
	template<class T>
void startWithArg(T arg)
{
  std::cout <<"start "<<std::endl;
  
  UdbLoginSucParams p = arg;
   std::cout <<"p  "<<p.isRelogin_ <<std::endl;
}

int main()
{

 char cstr[10] = {'1','2','0','3'};
 
 std::string str = cstr ;
 
 std::cout <<"str "<<str <<std::endl;
 
 UdbLoginSucParams p;
 p.isRelogin_ = true;
 startWithArg(p);
  
}

