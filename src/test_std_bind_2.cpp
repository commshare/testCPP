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
		//��Ա����ԭ�ͣ�Foo::f(int a, int b, int c);
	//ʹ��Foo::f, ��Ҫ�ĸ�������1.Foo���͵Ķ���(����ָ�������); 2~4��������ֵ��n1, n2, n3
	//�Է���ֵmfarg4�ĵ��ý���Ҫ4������: ��˳��󶨵�ռλ��_1, _2, _3, _4.
	auto bind_mf = std::bind(&Foo::f/*��Ա����ָ��*/, std::placeholders::_1, std::placeholders::_2);//, std::placeholders::_3, std::placeholders::_4);
	bind_mf(foo,100);
	return 0;
}
