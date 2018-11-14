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

//ʹ��bind���ྲ̬��Ա����
    Functor functor(std::bind(&Blas::addStatic,1,2));
  functor();
//ʹ��bind�����chengyuan����
    Functor functor2(std::bind(&Blas::add,blas,1,2));

    functor2();
}
int main(int argc,char** argv)
{
	testBasic();
    return 0;
}
/*
ԭ�ģ�https://blog.csdn.net/will_free/article/details/61622122 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
*/
