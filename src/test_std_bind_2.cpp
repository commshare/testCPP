#include <iostream>
#include <functional>

class Foo{
	public:
	void f(int num )
	{
		std::cout <<" num " << num <<std::endl;
	}
};

int main()
{
	Foo foo;
		//成员函数原型：Foo::f(int a, int b, int c);
	//使用Foo::f, 需要四个参数，1.Foo类型的对象(或其指针或引用); 2~4个参数则赋值给n1, n2, n3
	//对返回值mfarg4的调用将需要4个参数: 按顺序绑定到占位符_1, _2, _3, _4.
	auto bind_mf = std::bind(&Foo::f/*成员函数指针*/, std::placeholders::_1, std::placeholders::_2);//, std::placeholders::_3, std::placeholders::_4);
	bind_mf(foo,100);
	return 0;
}
