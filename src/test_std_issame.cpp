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
			  哦，因为这个const修饰的是说这个指针指向的内容不可改，不是这个指针本身的地址值不可改，所以无效了。
Removing const/volatile from?const?volatile?int?*?does not modify the type, because the pointer itself is neither const nor volatile.			  */
              << decay_equiv<const char * , char *>::value << '\n' //false
              << decay_equiv<const char  , char >::value << '\n' //true
              << decay_equiv<const char & , char >::value << '\n' ; //true
}
/*
--------------------- 
作者：尘中远 
来源：CSDN 
原文：https://blog.csdn.net/czyt1988/article/details/52812797 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
