#include <iostream>
#include <string>
#include <map>
using namespace std;
  
int main()
{
    map<string, int> langs;
  
    langs["Perl"] = 6;
    langs["C++"] = 2011;
    langs["Java"] = 8;
  
    cout << "size = " << langs.size() << endl; //3
    langs.clear();  //Çå¿Õmap
    cout << "size = " << langs.size() << endl; //0
    
    int &govalue = langs["go"];
    govalue = 1000;
        cout << "size = " << langs.size() << endl; //0

    map<string,int>::iterator it ;
    for (it = langs.begin();it != langs.end();it++ ){
    	cout<<"langs "<< it->second <<endl;
    	
	}
    return 0;
}
