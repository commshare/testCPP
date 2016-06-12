#include<iostream>
#include<typeinfo>
using namespace std;

/*
c++11 support auto
"GCC provides experimental support for the 2011 ISO C++ standard.
 This support can be enabled with the -std=c++11 or -std=gnu++11 compiler options; the former disables GNU extension."

*/
int main(){
	#if 0
	auto name=12;//"world";
	cout << name <<endl; 
	#endif
	int a=21;
	auto b=a;
	//typeid 可以修改变量或者数据类型的名字
	cout<<b<<endl;
	cout<<typeid(b).name() <<endl; 
	return 0;
}
