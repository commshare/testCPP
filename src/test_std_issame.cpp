#include <iostream>
#include <type_traits>

template <typename T, typename U>
struct decay_equiv : 
    std::is_same<typename std::decay<T>::type, U>::type 
{};

int main()
{
    std::cout << std::boolalpha
              << decay_equiv<int, int>::value << '\n'
              << decay_equiv<int&, int>::value << '\n'
              << decay_equiv<int&&, int>::value << '\n'
              << decay_equiv<const int&, int>::value << '\n'
              << decay_equiv<int[2], int*>::value << '\n'
              << decay_equiv<int(int), int(*)(int)>::value << '\n'
              /*
			  Ŷ����Ϊ���const���ε���˵���ָ��ָ������ݲ��ɸģ��������ָ�뱾��ĵ�ֵַ���ɸģ�������Ч�ˡ�
Removing const/volatile from?const?volatile?int?*?does not modify the type, because the pointer itself is neither const nor volatile.			  */
              << decay_equiv<const char * , char *>::value << '\n' //false
              << decay_equiv<const char  , char >::value << '\n' //true
              << decay_equiv<const char & , char >::value << '\n' ; //true
}
/*
--------------------- 
���ߣ�����Զ 
��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/czyt1988/article/details/52812797 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
*/
