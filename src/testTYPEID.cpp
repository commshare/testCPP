#include<iostream>
#include<typeinfo>
#include<string>
#include<vector>
using namespace std;

int func(int arg) {
	return 0;
} 

typedef int (*func_ptr)(int arg) ;

class Base {
	public :
		Base(){		}
}; 

int main(){
	int integer(1);
	double real(1.0);
	int array[10] = {1,2,3};
	
	int *array_header =array;
	
	string str;
	vector<int> int_vec;
	func_ptr f=func;
	cout<<"interger"<< typeid(integer).name() << endl;
	cout<<"real" <<typeid(real).name() <<endl;
	cout<<"array[100]"<<typeid(array).name() <<endl;
	cout<<"std::string" << typeid(str).name() <<endl;
	cout<<"funciton"<<typeid(func).name()<<endl;
	cout<<"function ptr "<<typeid(f).name() <<endl;
	cout << "customer class "<< typeid(Base()).name() <<endl;
	cout << "int "<< typeid(int).name() <<endl;
	cout<<"double "<<typeid(double).name() <<endl;
	cout<<"std::vector " <<typeid(std::vector<int>).name() <<endl;
	cout<<"Base " <<typeid(Base).name() <<endl;
	cout<<"Base * " <<typeid(Base *).name() <<endl;
	cout<<"Base &" <<typeid(Base &).name() <<endl;
	return 0;
}

/*
intergeri
reald
array[100]A10_i
std::stringSs
funcitonFiiE
function ptr PFiiE
customer class F4BasevE
int i
double d
std::vector St6vectorIiSaIiEE
Base 4Base
Base * P4Base
Base &4Base

--------------------------------
Process exited after 2.257 seconds with return value 0
请按任意键继续. . .

*/
