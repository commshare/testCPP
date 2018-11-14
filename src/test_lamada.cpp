
#pragma GCC diagnostic error "-std=c++11"  

/*
[capture list] (params list) mutable exception-> return type { function body }
capture list：捕获外部变量列表
params list：形参列表
mutable指示符：用来说用是否可以修改捕获的变量
exception：异常设定
return type：返回类型
function body：函数体
*/
 
#include<iostream>
using namespace std;
void testAuto(){
		//test auto in c++11
    cout<<"hello world!"<<endl;  
    auto i=10;  
    cout<<i<<endl;  
} 

/*
Lambda表达式可以使用其可见范围内的外部变量，但必须明确声明
明确声明哪些外部变量可以被该Lambda表达式使用）。那么，在哪里指定这些外部变量呢？
Lambda表达式通过在最前面的方括号[]来明确指明其内部可以访问的外部变量，
这一过程也称过Lambda表达式“捕获”了外部变量。
*/
void testLamada()
{
	//值捕获
	int a= 123;
	//注意末尾的； 
	auto f= [a] { cout <<a <<endl;} ;
	f(); //123
	
	//或通过“函数体”后面的‘()’传入参数
	/*编译不过啊：
	25	45	E:\mycode\testCPP\src\test_lamada.cpp	[Error] 'void x' has incomplete type
	*/
	 //auto x = [](int a){cout << a << endl;}(123); 
	 //下面这样可以编译过，但是怎么把外部变量a为123传递进去恩？ TODO
	 auto x = [](int a){cout << a << endl;}; 
	 
	 //引用捕获 引用捕获的变量使用的实际上就是该引用所绑定的对象。
	 a =888;
	 auto ff = [&a] {cout << a <<endl;} ;
	 ff(); //888
	 a =999;
	 ff(); //999
	 
	 //隐式捕获
	 /*
	 上面的值捕获和引用捕获都需要我们在捕获列表中显示列出Lambda表达式中使用的外部变量。
	 除此之外，我们还可以让编译器根据函数体中的代码来推断需要捕获哪些变量，
	 这种方式称之为隐式捕获。
	 隐式捕获有两种方式，分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，
	 [&]表示以引用捕获的方式捕获外部变量。
	 */
	 a= 555;
	 auto f3 = [=] {cout << a << endl;} ;//值捕获
	 a=777;
	 f3();  //打印的是555，不是777 

	 //隐式引用捕获示例：
	 auto f4 =[&] {cout << a <<endl;};
	 a=1000;
	 f4(); //打印的是1000 
	 
	 
	 /*
	 修改捕获变量
前面我们提到过，在Lambda表达式中，如果以传值方式捕获外部变量，则函数体中不能修改该外部变量，
否则会引发编译错误。
那么有没有办法可以修改值捕获的外部变量呢？这是就需要使用mutable关键字，
该关键字用以说明表达式体内的代码可以修改值捕获的变量
	 */ 
	 a=798;
	 auto f5 = [a]() mutable { cout << ++a ;} ;//
	 cout << a << endl; //798
	 f5();//799 被修改了 
} 
void testLambdaParam()
{
	// []	不捕获任何外部变量
	/*
	Lambda表达式的参数
Lambda表达式的参数和普通函数的参数类似，那么这里为什么还要拿出来说一下呢？原因是在Lambda表达式中传递参数还有一些限制，主要有以下几点：

参数列表中不能有默认参数
不支持可变参数
所有参数必须有参数名
*/
  int m = [] (int x ) 
  { 
  	return [] (int y) 
	  {
  		return y *2 ; 
 	  } 
 	  (x) + 6 ;
   }
   (5);
   //好像是这样的，5就是第一个匿名函数的x，然后x作为内部那个匿名函数的y传递
   //这样，匿名函数就返回5*2 ,第一个匿名函数的函数体是 return 10+6 
   //16
   std::cout << " m :" << m <<std::endl;
   
   //9
   std::cout <<"n: "<< [](int x,int y) {return x+y ;} (5,4) <<std::endl;
   
   //[=]	以值的形式捕获所有外部变量
   //113	39	E:\mycode\testCPP\src\test_lamada.cpp	[Error] expected '{' before '<' token 编译不过啊 
    //auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
//   auto gf = [] (int x) -> function <int (int) > { 
//   return [=] (int y) { return x+y; } ;
//   };
//   auto lf = gf(4);
   std::cout << lf(5) << std::endl;
   
}
class AAA{
	public:
		bool operator(int i) const {return i>50;}
};

void test1()
{
	vector<int > vec;
	//1 simple lambda 
	auto it = std::find_if(vec.begin(),vec.end(), [] (int i) {return i>50;
	});
	
	auto it2 = std::find_if(vec.begin(),vec.end(), AAA());
	
	//2 LAMBDA RETURN SYNTAX
	std::function < int (int ) > square = [] (int i) -> int {return i*i;}
	
	
	
}

//https://www.cnblogs.com/yyxt/p/4253088.html
int main()
{
	testAuto();
    
    //testLamada 捕获外部变量 
    testLamada();
    testLambdaParam();
    
    return 0;  
}

