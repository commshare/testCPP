#include <iostream>
#include <functional>

void f(int a, int b, int c)
{
	std::cout << "a=" << a << " " << "b=" << b << " " << "c=" << c << std::endl;
}

int ret4()
{
	std::cout << "ret4() calld" << std::endl;
	return 4;
}

void columns(int x)
{
	std::cout << "-----------------example:" << x << "-----------------" << std::endl;
}

class Foo 
{
public:
	void f(int a, int b, int c)
	{
		std::cout << "Foo::f():" << "a=" << a << " " << "b=" << b << " " << "c=" << c << std::endl;
	}

	int x = 1;
	int _a{ 100 };
};

//C++11 特性trailing return types   decltype是推倒类型,推导返回值类型
template <typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
{
	return t1 + t2;
}

//C++14 注意与上边的对比,不用显式写出推导返回值
template <typename T1, typename T2>
auto add2(const T1& t1, const T2& t2)
{
	return t1 + t2;
}





int main() 
{
	columns(1);
	//1.绑定最普通的函数
	auto empty_args = std::bind(f, 1, 2, 3);
	empty_args();//=f(1, 2, 3);

	columns(2);

	auto need_3args = std::bind(f, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	need_3args(1, 2, 3);//1,2,3
	need_3args(1, 2, 3, 4 == 4, 5);//1,2,3   4==4和5被抛弃,但是表达式会被执行
	need_3args(1, 2, 3, ret4());//1,2,3 ret4()返回值4被抛弃,但是函数会执行
	need_3args(1, 2, []()->int {std::cout << "This is a lambda ..." << std::endl; return 4; }());//也可以接受lambda表达式

	columns(3);

	//bind中参数的顺序对应原函数的顺序,其中placeholders的值对应新函数的顺序
	auto need_2args = std::bind(f, 1, std::placeholders::_2, std::placeholders::_1);
	need_2args(4, 5);//1,5,4

	columns(4);

	//bind 也可以绑定lambda函数
	auto lambda_func = [](int x, int y)->int {return x + y; };
	std::cout << lambda_func(10, 20) << std::endl;//30

	auto func1 = std::bind(lambda_func, std::placeholders::_2, 1);
	std::cout << func1(10, 20) << std::endl;//21
	std::cout << std::bind(lambda_func, std::placeholders::_2, 1)(10, 20) << std::endl;//21 直接调用

	columns(5);

	//使用bind适配一个函数 使用function接受
	auto func2 = [](int x, int y)->int {std::cout << "y=" << y << std::endl; return(x + y); };

	std::function<int(int)> func_with_args = std::bind(func2, 10, std::placeholders::_1);
	func_with_args(5);//5
	std::cout << func_with_args(5) << std::endl;//15

	std::function<void(int)> sunc_with_noargs = std::bind(func2, 10, std::placeholders::_1);
	sunc_with_noargs(5);//5  但是没有了返回值,使用场景不多,不推荐使用

	columns(6);
	
	//绑定成员函数
	Foo foo;
	Foo& foo_ref = foo;

	//成员函数原型：Foo::f(int a, int b, int c);
	//使用Foo::f, 需要四个参数，1.Foo类型的对象(或其指针或引用); 2~4个参数则赋值给n1, n2, n3
	//对返回值mfarg4的调用将需要4个参数: 按顺序绑定到占位符_1, _2, _3, _4.
	auto bind_mf = std::bind(&Foo::f/*成员函数指针*/, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	bind_mf(foo, 10, 20, 30);//第一个占位符必须代表对象
	
	// bind成员变量，其第一个参数必须是该类型的一个对象(或对象或引用), 指针不行
	auto bind_mv = std::bind(&Foo::_a, std::placeholders::_1);
	std::cout << bind_mv(foo) << std::endl;//100
	std::cout << bind_mv(foo_ref) << std::endl;//100
	//cout << bind_mv(&foo);        // error, 成员变量不能用对象指针来绑定

	columns(7);

	//绑定函数模板
	auto bind_add = std::bind(add<int, double>, std::placeholders::_1, 2.5);
	std::cout << "bind_add=" << bind_add(2) << std::endl;//4.5 推导返回值类型
	auto bind_add2 = std::bind(add2<float, int>, std::placeholders::_1, std::placeholders::_2);
	std::cout << "bind_add2=" << bind_add2(1.1, 2) << std::endl;//3.1

	columns(8);

	//嵌套绑定
	//嵌套绑定的bind在使用外层bind()中的placeholders,嵌套绑定中的函数在调用时会自动执行内部的绑定(重要)
	//bind函数中的参数顺序对应元函数的顺序, 占位符placeholders对应新函数中的顺序
	//当调用时,将实参对应填写到placeholders
	auto addself = [](int x)->int {std::cout << "addself() calld" << std::endl; return x + 1; };

	//std::placeholders::_1绑定成员时,默认为对象或对象的引用(如果是类,可以指定为指针)
	auto nested_fx = std::bind(&Foo::f, foo, std::placeholders::_1, std::bind(addself, std::placeholders::_2), std::placeholders::_2);
	nested_fx(1, 3); //=foo.f(1, 4, 3);
	nested_fx(7, 9); //=foo.f(7, 10, 9);

	auto nested_f = std::bind(&Foo::f, std::placeholders::_1, std::placeholders::_2, std::bind(addself, std::placeholders::_2), std::placeholders::_3);
	nested_f(foo, 1, 3);//1, 2, 3
	nested_f(foo, 1, 3, 7);//1, 2, 3

	//reference_wrapper<T>类型, 实现绑定引用
	int x(10);
	//第二个参数使用引用x，第三个参数使用值x
	auto bind_ref = std::bind(&Foo::f, foo, std::cref(x), x, std::ref(x));
	bind_ref();// 10 10 10;
	x = 100;
	bind_ref();// 100 10 100; 第二个参数跟着x变化了，第三个则没变


	std::cin.get();
	return 0;
}


//--------------------- 
//作者：朱 宏江 
//来源：CSDN 
//原文：https://blog.csdn.net/weixin_43220160/article/details/84792375 
//版权声明：本文为博主原创文章，转载请附上博文链接！

