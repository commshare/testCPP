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

//C++11 ����trailing return types   decltype���Ƶ�����,�Ƶ�����ֵ����
template <typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
{
	return t1 + t2;
}

//C++14 ע�����ϱߵĶԱ�,������ʽд���Ƶ�����ֵ
template <typename T1, typename T2>
auto add2(const T1& t1, const T2& t2)
{
	return t1 + t2;
}





int main() 
{
	columns(1);
	//1.������ͨ�ĺ���
	auto empty_args = std::bind(f, 1, 2, 3);
	empty_args();//=f(1, 2, 3);

	columns(2);

	auto need_3args = std::bind(f, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	need_3args(1, 2, 3);//1,2,3
	need_3args(1, 2, 3, 4 == 4, 5);//1,2,3   4==4��5������,���Ǳ��ʽ�ᱻִ��
	need_3args(1, 2, 3, ret4());//1,2,3 ret4()����ֵ4������,���Ǻ�����ִ��
	need_3args(1, 2, []()->int {std::cout << "This is a lambda ..." << std::endl; return 4; }());//Ҳ���Խ���lambda���ʽ

	columns(3);

	//bind�в�����˳���Ӧԭ������˳��,����placeholders��ֵ��Ӧ�º�����˳��
	auto need_2args = std::bind(f, 1, std::placeholders::_2, std::placeholders::_1);
	need_2args(4, 5);//1,5,4

	columns(4);

	//bind Ҳ���԰�lambda����
	auto lambda_func = [](int x, int y)->int {return x + y; };
	std::cout << lambda_func(10, 20) << std::endl;//30

	auto func1 = std::bind(lambda_func, std::placeholders::_2, 1);
	std::cout << func1(10, 20) << std::endl;//21
	std::cout << std::bind(lambda_func, std::placeholders::_2, 1)(10, 20) << std::endl;//21 ֱ�ӵ���

	columns(5);

	//ʹ��bind����һ������ ʹ��function����
	auto func2 = [](int x, int y)->int {std::cout << "y=" << y << std::endl; return(x + y); };

	std::function<int(int)> func_with_args = std::bind(func2, 10, std::placeholders::_1);
	func_with_args(5);//5
	std::cout << func_with_args(5) << std::endl;//15

	std::function<void(int)> sunc_with_noargs = std::bind(func2, 10, std::placeholders::_1);
	sunc_with_noargs(5);//5  ����û���˷���ֵ,ʹ�ó�������,���Ƽ�ʹ��

	columns(6);
	
	//�󶨳�Ա����
	Foo foo;
	Foo& foo_ref = foo;

	//��Ա����ԭ�ͣ�Foo::f(int a, int b, int c);
	//ʹ��Foo::f, ��Ҫ�ĸ�������1.Foo���͵Ķ���(����ָ�������); 2~4��������ֵ��n1, n2, n3
	//�Է���ֵmfarg4�ĵ��ý���Ҫ4������: ��˳��󶨵�ռλ��_1, _2, _3, _4.
	auto bind_mf = std::bind(&Foo::f/*��Ա����ָ��*/, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	bind_mf(foo, 10, 20, 30);//��һ��ռλ������������
	
	// bind��Ա���������һ�����������Ǹ����͵�һ������(����������), ָ�벻��
	auto bind_mv = std::bind(&Foo::_a, std::placeholders::_1);
	std::cout << bind_mv(foo) << std::endl;//100
	std::cout << bind_mv(foo_ref) << std::endl;//100
	//cout << bind_mv(&foo);        // error, ��Ա���������ö���ָ������

	columns(7);

	//�󶨺���ģ��
	auto bind_add = std::bind(add<int, double>, std::placeholders::_1, 2.5);
	std::cout << "bind_add=" << bind_add(2) << std::endl;//4.5 �Ƶ�����ֵ����
	auto bind_add2 = std::bind(add2<float, int>, std::placeholders::_1, std::placeholders::_2);
	std::cout << "bind_add2=" << bind_add2(1.1, 2) << std::endl;//3.1

	columns(8);

	//Ƕ�װ�
	//Ƕ�װ󶨵�bind��ʹ�����bind()�е�placeholders,Ƕ�װ��еĺ����ڵ���ʱ���Զ�ִ���ڲ��İ�(��Ҫ)
	//bind�����еĲ���˳���ӦԪ������˳��, ռλ��placeholders��Ӧ�º����е�˳��
	//������ʱ,��ʵ�ζ�Ӧ��д��placeholders
	auto addself = [](int x)->int {std::cout << "addself() calld" << std::endl; return x + 1; };

	//std::placeholders::_1�󶨳�Աʱ,Ĭ��Ϊ�������������(�������,����ָ��Ϊָ��)
	auto nested_fx = std::bind(&Foo::f, foo, std::placeholders::_1, std::bind(addself, std::placeholders::_2), std::placeholders::_2);
	nested_fx(1, 3); //=foo.f(1, 4, 3);
	nested_fx(7, 9); //=foo.f(7, 10, 9);

	auto nested_f = std::bind(&Foo::f, std::placeholders::_1, std::placeholders::_2, std::bind(addself, std::placeholders::_2), std::placeholders::_3);
	nested_f(foo, 1, 3);//1, 2, 3
	nested_f(foo, 1, 3, 7);//1, 2, 3

	//reference_wrapper<T>����, ʵ�ְ�����
	int x(10);
	//�ڶ�������ʹ������x������������ʹ��ֵx
	auto bind_ref = std::bind(&Foo::f, foo, std::cref(x), x, std::ref(x));
	bind_ref();// 10 10 10;
	x = 100;
	bind_ref();// 100 10 100; �ڶ�����������x�仯�ˣ���������û��


	std::cin.get();
	return 0;
}


//--------------------- 
//���ߣ��� �꽭 
//��Դ��CSDN 
//ԭ�ģ�https://blog.csdn.net/weixin_43220160/article/details/84792375 
//��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�

