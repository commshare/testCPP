#include<algorithm>
#include<iostream>

#if 0 
int main()
{
? ? ? ? int array[5]={1, 3, 5, 7, 9}; 

? ? ? ? //����ֵΪ 7 ����������
? ? ? ? int* iterator=std::find(
? ? ? ? ? ? ? ? static_cast<int*>(array), //��ʼ������
? ? ? ? ? ? ? ? static_cast<int*>(array)+5, //�������յ�
? ? ? ? ? ? ? ? 7 //��Ҫ���ҵ�ֵ
? ? ? ? ? ? ? ? ); 
? ? ? ? ? ? ? ? 
? ? ? ? //��ӡ�����Ľ������ 7
? ? ? ? std::cout << *iterator << std::endl;
? ? ? ? 
? ? ? ? return 0
}
--------------------- 
���ߣ�zyyoung 
��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/zyyoung/article/details/6093971 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
#else
/*
�ڲ��ҵĹ��������Զ���ıȽϣ���˵��������ص�ֵ��������Ӧ���� value ���Խ�����ȱȽϣ���������޷�ͨ�����룬����˶�����������ʱ������Ϣ��
*/
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
