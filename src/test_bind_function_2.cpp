#include<iostream>
#include<functional>

typedef std::function<void()> Functor;
typedef std::function<void(int,int)> Functor2;
class Blas
{
    public:
    	//设置回调，引用？ 
        void setCallBack(const Functor& cb)
        {functor = cb;};

        void printFunctor()
        {functor();};
        
        void setCallBack2(const Functor2& cb)
         {functor2 = cb;};

       void printFunctor2()
      {functor2(x,y);};
        
    private:
        Functor functor;  //回调 
          Functor2 functor2;  //回调 
        int x = 1000;
        int y = 1000;
};

class Atlas
{
    public:
        Atlas(int x_) : x(x_)
        {
            //使用当前类的静态成员函数

           blas.setCallBack(std::bind(&addStatic,x,2));
        //使用当前类的非静态成员函数 ，绑定的对象是this ？ this 是当前Atlas的对象吧 
                  blas.setCallBack(std::bind(&Atlas::add,this,x,2));
        }
        Atlas(int x_,int y_) : x(x_),y(y_)
        {
            //使用当前类的非静态成员函数
            blas.setCallBack(std::bind(&Atlas::add,this,x,20));
        }
        Atlas(int x_,int y_,int z_) : x(x_),y(y_),z(z_)
        {
            //使用当前类的非静态成员函数 
            blas.setCallBack2(std::bind(&Atlas::add,this,std::placeholders::_1,std::placeholders::_2));
        }

       
        void print()
        {
            blas.printFunctor();
        }
        void print2()
        {
            blas.printFunctor2();
        }
      
    private:
        void add(int a,int b)
        {
        	std::cout<<"this is add "<<std::endl;
            std::cout << a+b << std::endl;
             std::cout << y << std::endl;
        }

        //回调是一个void（） 类型 
        static void addStatic(int a,int b)
        {
            std::cout << a+b << std::endl;
        }

        Blas blas; //blas需要的回调，在Atlas实现 
        int x,y;
        int z;
         Functor functor;
};

int main(int argc,char** argv)
{
    Atlas atlas(5);   //设置了x进去，并且设置了回调 
    atlas.print(); // 使用了设置进去的回调 
    
    Atlas atlas1(6,10);
    atlas1.print();
    
    Atlas atlas2(6,200,100);
    atlas2.print2();
return 0;
}

//原文：https://blog.csdn.net/will_free/article/details/61622122 
/*
两个函数在Atlas类中，并且可以自由操作Atlas的数据成员。尽管是将add()系列的函数封装成函数对象传入Blas中，并且在Blas类中调用，
但是它们仍然具有操作Atlas数据成员的功能，在两个类之间形成了弱的耦合作用。但是如果要在两个类之间形成弱的耦合作用，必须在使用std::bind()封装时，
向其中传入this指针：

这个this指针弱耦合了两个类， 
std::bind(&Atlas::add,this,1,2);

*/ 
