#include<iostream>
//#include "comm.h"  
 #include <stdint.h>
using namespace std;
//typedef unsigned char uint8_t
#include <sstream> // for istringstream 

//
//typedef signed char int8_t ;
//
//typedef signed int int16_t ;
//
//typedef signed long int int32_t;
//
//typedef signed long long int int64_t ;



bool Dump(const std::string &content)
{
  std::istringstream f(content); //istringstream，由 istream 派生而来，提供读 string 的功能。 
  std::string line;

  uint32_t i = 0;
  while (std::getline(f, line)) { //从f读取，读到line里 
    i++;
    //FUNLOG (Debug, "%04u: %s", i, line.c_str());  //打印line 
    std::cout<<"line "<<i<<" :"<<line<<endl;
  }
  return true;
}

class MString {
	public:
	MString(){
			cout<<"constructor "<<endl;
	};

	
	~MString(){
		cout<<"de constructor "<<endl;;
	};
	
	
	string myString(){
	return 	"hello china";
	}

};
        void dumpddd(std::ostringstream& os){
            os << "{--dumpddd---}"<<"\n";
        }
 void dumpccc(std::ostringstream& os){
 	 uint32_t hello;
 	 hello=100;
 	  os <<"{ tcnt "<<87 <<" tms "<<8777<<" }";
 	 os <<"  dumpccc1 " << hello+1<<dumpddd;
 	 os <<"  dumpccc2 " << hello+2<<dumpddd;
 	 os <<"  dumpccc3 " << hello+3<<dumpddd;
 }
 void dumpaaa(std::ostringstream& os){
 			uint8_t strategyId = 0 ;
			 /*貌似要使用unsigned*/ 			
            os <<"  strategyid " <<(unsigned) strategyId <<std::endl;
            os <<"  normal :" ;dumpccc(os);
            os <<"  resend :" ;dumpccc(os);
            os <<"  all :" ;dumpccc(os);
        }
 void dumpbbb(std::ostringstream& os){
 		uint32_t size =2 ;
            os <<" size : "<< size << std::endl;
            dumpaaa(os) ;
}

 
int huichehuanhang()  
{  
    cout << "this is the first line\n";  
    cout << "this is the second line\r";  
    cout << "this is the third line\n";  
    cout << "this is the fouth line\r";  
    cout << "this is the fifth line\n";  
    cout << "end" ;  
    return 0;  
}  


int main(){
	string con = "zhangbin";
	Dump(con);
	MString m;
	cout<<"----call dump :"<<endl; 
	Dump(m.myString());

	 std::ostringstream os;
	 dumpbbb(os);
	 cout <<"cout "<<os.str();
	 cout <<std::endl;
	 printf("print1 %s",os.str().c_str());
	 	 cout <<std::endl;
	 printf("print2 %s",os.str().data());
	 
	 huichehuanhang();
	return 0;
}


 
