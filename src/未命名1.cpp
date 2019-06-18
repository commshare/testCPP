#include<algorithm>
#include<iostream>

#if 0 
int main()
{
? ? ? ? int array[5]={1, 3, 5, 7, 9}; 

? ? ? ? //查找值为 7 的整数对象
? ? ? ? int* iterator=std::find(
? ? ? ? ? ? ? ? static_cast<int*>(array), //起始迭代器
? ? ? ? ? ? ? ? static_cast<int*>(array)+5, //迭代器终点
? ? ? ? ? ? ? ? 7 //需要查找的值
? ? ? ? ? ? ? ? ); 
? ? ? ? ? ? ? ? 
? ? ? ? //打印出来的结果将是 7
? ? ? ? std::cout << *iterator << std::endl;
? ? ? ? 
? ? ? ? return 0
}
--------------------- 
作者：zyyoung 
来源：CSDN 
原文：https://blog.csdn.net/zyyoung/article/details/6093971 
版权声明：本文为博主原创文章，转载请附上博文链接！
#else

int main()

{
	int arr[5] = {1,3,45,6};
	//45
	int * iter = std::find(static_cast<int*> (arr),
	static_cast<int * > (arr + 4),
	45
	);
	std::cout << *iter <<std::endl; 
 } 
#endif 
