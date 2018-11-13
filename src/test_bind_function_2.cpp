#include<iostream>
#include<functional>

typedef std::function<void()> Functor;
typedef std::function<void(int,int)> Functor2;
class Blas
{
    public:
    	//���ûص������ã� 
        void setCallBack(const Functor& cb)
        {functor = cb;};

        void printFunctor()
        {functor();};
        
        void setCallBack2(const Functor2& cb)
         {functor2 = cb;};

       void printFunctor2()
      {functor2(x,y);};
        
    private:
        Functor functor;  //�ص� 
          Functor2 functor2;  //�ص� 
        int x = 1000;
        int y = 1000;
};

class Atlas
{
    public:
        Atlas(int x_) : x(x_)
        {
            //ʹ�õ�ǰ��ľ�̬��Ա����

           blas.setCallBack(std::bind(&addStatic,x,2));
        //ʹ�õ�ǰ��ķǾ�̬��Ա���� ���󶨵Ķ�����this �� this �ǵ�ǰAtlas�Ķ���� 
                  blas.setCallBack(std::bind(&Atlas::add,this,x,2));
        }
        Atlas(int x_,int y_) : x(x_),y(y_)
        {
            //ʹ�õ�ǰ��ķǾ�̬��Ա����
            blas.setCallBack(std::bind(&Atlas::add,this,x,20));
        }
        Atlas(int x_,int y_,int z_) : x(x_),y(y_),z(z_)
        {
            //ʹ�õ�ǰ��ķǾ�̬��Ա���� 
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

        //�ص���һ��void���� ���� 
        static void addStatic(int a,int b)
        {
            std::cout << a+b << std::endl;
        }

        Blas blas; //blas��Ҫ�Ļص�����Atlasʵ�� 
        int x,y;
        int z;
         Functor functor;
};

int main(int argc,char** argv)
{
    Atlas atlas(5);   //������x��ȥ�����������˻ص� 
    atlas.print(); // ʹ�������ý�ȥ�Ļص� 
    
    Atlas atlas1(6,10);
    atlas1.print();
    
    Atlas atlas2(6,200,100);
    atlas2.print2();
return 0;
}

//ԭ�ģ�https://blog.csdn.net/will_free/article/details/61622122 
/*
����������Atlas���У����ҿ������ɲ���Atlas�����ݳ�Ա�������ǽ�add()ϵ�еĺ�����װ�ɺ���������Blas�У�������Blas���е��ã�
����������Ȼ���в���Atlas���ݳ�Ա�Ĺ��ܣ���������֮���γ�������������á��������Ҫ��������֮���γ�����������ã�������ʹ��std::bind()��װʱ��
�����д���thisָ�룺

���thisָ��������������࣬ 
std::bind(&Atlas::add,this,1,2);

*/ 
