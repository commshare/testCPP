#include <iostream>
#include <ctype.h>
 #include <stdint.h>
#include <time.h> 
using namespace std; 


class f {
	public :
	f(string n):v(0){
		name = n;
		cout <<"constructor "<<name <<endl;
	}
	~f(){
		cout <<"deconstructor "<<name<<endl;
	}
     string name;
	 int v ;
	 add(f cf){
	 	v = cf.v ;
	 }
	 addref(f &cf){
	 	v = cf.v;
	 }
};

int main(){
	f ff("ff");
	f cf("cf");
	//cf.v = 100;

	cout <<"use by value "<<endl;
	ff.add(cf); //应该会有一个 构造 ,结果没有，只有一个析构 
	cout<<endl;  
	cout <<"use by ref " <<endl; 
	ff.addref(cf);
	return 0;
}
/*
constructor ff
constructor cf

use by value
deconstructor cf  没看到这个的构造呢？ 

use by ref

deconstructor cf
deconstructor ff

*/
