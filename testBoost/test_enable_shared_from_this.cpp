
#include<iostream>
#include<string>
#include<boost/shared_ptr.hpp>
#include<boost/enable_shared_from_this.hpp>
using namespace std;
using namespace boost;
/*
http://blog.sina.com.cn/s/blog_5f435c130101hpzi.html
1. 如果一个类继承了boost::enable_shared_from_this，那么之后创建这个类的对象的时候，一定要用shared_ptr封装起来。
 2. 一定不要在构造函数和析构函数里面调用shared_from_this()，否则会引起十分诡异的错误。
 
 
 boost文档中首先讲了enable_shared_from_this的作用 : The header <boost/enable_shared_from_this.hpp> defines the class template enable_shared_from_this.
  It is used as a base class that allows a shared_ptr to the current object to be obtained from within a member function.
 
*/
/*
http://my.oschina.net/lingluonianhua/blog/212533
*/
class MyPoint  : public boost::enable_shared_from_this<MyPoint>{
	public :
		int i;
	public:
		
	MyPoint(){cout<<"MyPoint"<<endl;
	i=0;
	}
	~MyPoint(){
		cout<<"~MyPoint"<<endl;
		cout<<"i["<<i<<"]"<<endl;
	}
	
	//
	boost::shared_ptr<MyPoint> GetPoint2(){
		return shared_from_this();
	}
  boost::shared_ptr<MyPoint> GetPoint1()
    {
        return boost::shared_ptr<MyPoint>(this);   //错误，将返回一个新的引用计数
    }
};

int main(){
	boost:shared_ptr <MyPoint> p1(new MyPoint());
		cout<<"p1.use_count["<<p1.use_count()<<"]"<<endl; //这时候还是 1
		(*p1).i=100;
	boost::shared_ptr<MyPoint> p2=p1->GetPoint2(); /*引用计数变为2了*/
	cout<<"p1 i["<<(*p1).i<<"] p2 i["<<(*p2).i<<"]"<<endl;
	(*p2).i=200;
	cout<<"after p2 i = 200: p1 i["<<(*p1).i<<"] p2 i["<<(*p2).i<<"]"<<endl;
		/*到了这里就变成了2*/ 
	cout<<"p1.use_count["<<p1.use_count()<<"] p2.use_count()["<<p2.use_count()<<"] " <<endl; //输出引用计数情况
	boost::shared_ptr<MyPoint> p3= p1->GetPoint1(); /*这个就是1，说明这是一个新的*/
	/*到了这里就还是2*/ 
	cout<<"after p3 : p1.use_count["<<p1.use_count()<<"] p2.use_count()["<<p2.use_count()<<"] p3.use_count()["<<p3.use_count()<<"]" <<endl; //输出引用计数情况
	p1.reset(); //内存将被释放
	cout<<"after rest p1 : p1.use_count["<<p1.use_count()<<"] p2.use_count()["<<p2.use_count()<<"] p3.use_count()["<<p3.use_count()<<"]" <<endl; //输出引用计数情况return 0;
	
	cout<<"p3 i["<<(*p3).i<<"]"<<endl;
	cout<<"before p3 reset :  p3.use_count()["<<p3.use_count()<<"]" <<endl;
	p3.reset();
	cout<<"after p3 reset :  p3.use_count()["<<p3.use_count()<<"]" <<endl;
}

/*
MyPoint
p1.use_count[1]
p1 i[100] p2 i[100]
after p2 i = 200: p1 i[200] p2 i[200]
p1.use_count[2] p2.use_count()[2]
after p3 : p1.use_count[2] p2.use_count()[2] p3.use_count()[1]
after rest p1 : p1.use_count[0] p2.use_count()[1] p3.use_count()[1]
p3 i[200]
before p3 reset :  p3.use_count()[1]
~MyPoint
i[200]
after p3 reset :  p3.use_count()[0]
~MyPoint
i[200]

--------------------------------
Process exited after 0.02171 seconds with return value 0
请按任意键继续. . .

*/ 
