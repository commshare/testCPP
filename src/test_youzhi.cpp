#include<iostream>

void use_value (int p)
{

std::cout << p << std::endl;

}

void use_value2 (int &&p)
{

std::cout << p << std::endl;

}
int main()

{
	int && a = 9;
	use_value(a);
	//21	14	E:\rrrtc\testCpp\test_youzhi.cpp	[Error] cannot bind 'int' lvalue to 'int&&'
	//10	6	E:\rrrtc\testCpp\test_youzhi.cpp	[Note] initializing argument 1 of 'void use_value2(int&&)'
	//use_value2(a);
	return 0;
}
