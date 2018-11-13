#include<iostream>
#include<functional>
typedef std::function<void()> Functor;
class Blas
{
    public:
        void add(int a,int b)
        {
            std::cout << a+b << std::endl;
        }

        static void addStatic(int a,int b)
        {
            std::cout << a+b << std::endl;
        }
};
void testBasic()
{
	    Blas blas;

//使用bind绑定类静态成员函数
    Functor functor(std::bind(&Blas::addStatic,1,2));
  functor();
//使用bind绑定类的chengyuan函数
    Functor functor2(std::bind(&Blas::add,blas,1,2));

    functor2();
}
int main(int argc,char** argv)
{
	testBasic();
    return 0;
}
/*
原文：https://blog.csdn.net/will_free/article/details/61622122 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
