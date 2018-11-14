#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include<algorithm>
#include <functional>
#include <memory>

using namespace std;

//declare a template
typedef std::function <int (int)> Functional;

//normal funciton
int TestFunc(int a)
{return a;
}
//lambda expression

auto lambda = [](int a)->int{return a;};


//functor仿函数
class Functor
{
	public:
		int operator()(int a)
		{
			return a;
		}
};


//类的成员函数和类的静态成员函数
class CTest
{
	public:
		int Func(int a)
		{
			return a;
		}
		static int SFunc(int a)
		{
			return a;
		}
};


   
class A  
{  
public:  
    int Func(int x, int y){
    	return x+y;
	};  
    
};  
   	int Func(int x, int y){
   		return x+y;
	   };  
   void tt() 
   {
   	//bf1是把一个两个参数普通函数的第一个参数绑定为10，生成了一个新的一个参数的可调用实体体 
		auto bf1 = std::bind(Func, 10, std::placeholders::_1);  
		bf1(20); ///< same as Func(10, 20)  
		//类的对象a 
		A a;  
		//bf2是把一个类成员函数绑定了类对象，生成了一个像普通函数一样的新的可调用实体; 
	auto bf2 = std::bind(&A::Func, a, std::placeholders::_1, std::placeholders::_2);  
	bf2(10, 20); ///< same as a.Func(10, 20)  
   
   // bf3是把类成员函数绑定了类对象和第二个参数， 
   //1这个位置是100，看bf1，应该是第一个形参，这里是不是搞错了？ 
	std::function< int(int)> bf3 = std::bind(&A::Func, a, std::placeholders::_1, 100);  
	bf3(10); ///< same as a.Func(10, 100)  
   }
/*
（1）bind预先绑定的参数需要传具体的变量或值进去，对于预先绑定的参数，是pass-by-value的
（2）对于不事先绑定的参数，需要传std::placeholders进去，从_1开始，依次递增。placeholder是pass-by-reference的
（3）bind的返回值是可调用实体，可以直接赋给std::function对象
（4）对于绑定的指针、引用类型的参数，使用者需要保证在可调用实体调用之前，这些参数是可用的
（5）类的this可以通过对象或者指针来绑定
*/ 


int main(int argc,char * argv[])
{
	 //封装普通函数
	 
    Functional obj = TestFunc;
	int res = obj(0);
    cout << "normal function : " << res << endl;
    
    
     //封装lambda表达式
    obj = lambda;
    res = obj(1);
    cout << "lambda expression : " << res << endl;
    
    //封装仿函数
    Functor functorObj;
    obj = functorObj;
    res = obj(2);
    cout << "functor : " << res << endl;
    
    /*
	function模板类和bind模板函数，使用它们可以实现类似函数指针的功能，但却比函数指针更加灵活，
	特别是函数指向类的非静态成员函数时。

std::function可以绑定到全局函数/类静态成员函数(类静态成员函数与全局函数没有区别),如果要绑定到类的非静态成员函数，
则需要使用std::bind。
	*/
     //封装类的成员函数和static成员函数
    CTest t;
    obj = std::bind(&CTest::Func, &t, std::placeholders::_1);
    res = obj(3);
    cout << "member function : " << res << endl;
 
    obj = CTest::SFunc;
    res = obj(4);
    cout << "static member function : " << res << endl;
    
    tt();
    
    return 0;
}
/*
关于可调用实体转换为std::function对象需要遵守以下两条原则：
转换后的std::function对象的参数能转换为可调用实体的参数；
可调用实体的返回值能转换为std::function对象的返回值。
std::function对象最大的用处就是在实现函数回调，使用者需要注意，
它不能被用来检查相等或者不相等，但是可以与NULL或者nullptr进行比较。
*/
//https://blog.csdn.net/zeqi1991/article/details/73727458?locationNum=8&fps=1
