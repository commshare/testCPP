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


//functor�º���
class Functor
{
	public:
		int operator()(int a)
		{
			return a;
		}
};


//��ĳ�Ա��������ľ�̬��Ա����
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
   	//bf1�ǰ�һ������������ͨ�����ĵ�һ��������Ϊ10��������һ���µ�һ�������Ŀɵ���ʵ���� 
		auto bf1 = std::bind(Func, 10, std::placeholders::_1);  
		bf1(20); ///< same as Func(10, 20)  
		//��Ķ���a 
		A a;  
		//bf2�ǰ�һ�����Ա�������������������һ������ͨ����һ�����µĿɵ���ʵ��; 
	auto bf2 = std::bind(&A::Func, a, std::placeholders::_1, std::placeholders::_2);  
	bf2(10, 20); ///< same as a.Func(10, 20)  
   
   // bf3�ǰ����Ա�������������͵ڶ��������� 
   //1���λ����100����bf1��Ӧ���ǵ�һ���βΣ������ǲ��Ǹ���ˣ� 
	std::function< int(int)> bf3 = std::bind(&A::Func, a, std::placeholders::_1, 100);  
	bf3(10); ///< same as a.Func(10, 100)  
   }
/*
��1��bindԤ�Ȱ󶨵Ĳ�����Ҫ������ı�����ֵ��ȥ������Ԥ�Ȱ󶨵Ĳ�������pass-by-value��
��2�����ڲ����Ȱ󶨵Ĳ�������Ҫ��std::placeholders��ȥ����_1��ʼ�����ε�����placeholder��pass-by-reference��
��3��bind�ķ���ֵ�ǿɵ���ʵ�壬����ֱ�Ӹ���std::function����
��4�����ڰ󶨵�ָ�롢�������͵Ĳ�����ʹ������Ҫ��֤�ڿɵ���ʵ�����֮ǰ����Щ�����ǿ��õ�
��5�����this����ͨ���������ָ������
*/ 


int main(int argc,char * argv[])
{
	 //��װ��ͨ����
	 
    Functional obj = TestFunc;
	int res = obj(0);
    cout << "normal function : " << res << endl;
    
    
     //��װlambda���ʽ
    obj = lambda;
    res = obj(1);
    cout << "lambda expression : " << res << endl;
    
    //��װ�º���
    Functor functorObj;
    obj = functorObj;
    res = obj(2);
    cout << "functor : " << res << endl;
    
    /*
	functionģ�����bindģ�庯����ʹ�����ǿ���ʵ�����ƺ���ָ��Ĺ��ܣ���ȴ�Ⱥ���ָ�������
	�ر��Ǻ���ָ����ķǾ�̬��Ա����ʱ��

std::function���԰󶨵�ȫ�ֺ���/�ྲ̬��Ա����(�ྲ̬��Ա������ȫ�ֺ���û������),���Ҫ�󶨵���ķǾ�̬��Ա������
����Ҫʹ��std::bind��
	*/
     //��װ��ĳ�Ա������static��Ա����
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
���ڿɵ���ʵ��ת��Ϊstd::function������Ҫ������������ԭ��
ת�����std::function����Ĳ�����ת��Ϊ�ɵ���ʵ��Ĳ�����
�ɵ���ʵ��ķ���ֵ��ת��Ϊstd::function����ķ���ֵ��
std::function���������ô�������ʵ�ֺ����ص���ʹ������Ҫע�⣬
�����ܱ����������Ȼ��߲���ȣ����ǿ�����NULL����nullptr���бȽϡ�
*/
//https://blog.csdn.net/zeqi1991/article/details/73727458?locationNum=8&fps=1
