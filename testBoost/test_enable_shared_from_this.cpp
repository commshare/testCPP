
#include<iostream>
#include<string>
#include<boost/shared_ptr.hpp>
#include<boost/enable_shared_from_this.hpp>
using namespace std;
using namespace boost;
/*
http://blog.sina.com.cn/s/blog_5f435c130101hpzi.html
1. ���һ����̳���boost::enable_shared_from_this����ô֮�󴴽������Ķ����ʱ��һ��Ҫ��shared_ptr��װ������
 2. һ����Ҫ�ڹ��캯�������������������shared_from_this()�����������ʮ�ֹ���Ĵ���
 
 
 boost�ĵ������Ƚ���enable_shared_from_this������ : The header <boost/enable_shared_from_this.hpp> defines the class template enable_shared_from_this.
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
        return boost::shared_ptr<MyPoint>(this);   //���󣬽�����һ���µ����ü���
    }
};

int main(){
	boost:shared_ptr <MyPoint> p1(new MyPoint());
		cout<<"p1.use_count["<<p1.use_count()<<"]"<<endl; //��ʱ���� 1
		(*p1).i=100;
	boost::shared_ptr<MyPoint> p2=p1->GetPoint2(); /*���ü�����Ϊ2��*/
	cout<<"p1 i["<<(*p1).i<<"] p2 i["<<(*p2).i<<"]"<<endl;
	(*p2).i=200;
	cout<<"after p2 i = 200: p1 i["<<(*p1).i<<"] p2 i["<<(*p2).i<<"]"<<endl;
		/*��������ͱ����2*/ 
	cout<<"p1.use_count["<<p1.use_count()<<"] p2.use_count()["<<p2.use_count()<<"] " <<endl; //������ü������
	boost::shared_ptr<MyPoint> p3= p1->GetPoint1(); /*�������1��˵������һ���µ�*/
	/*��������ͻ���2*/ 
	cout<<"after p3 : p1.use_count["<<p1.use_count()<<"] p2.use_count()["<<p2.use_count()<<"] p3.use_count()["<<p3.use_count()<<"]" <<endl; //������ü������
	p1.reset(); //�ڴ潫���ͷ�
	cout<<"after rest p1 : p1.use_count["<<p1.use_count()<<"] p2.use_count()["<<p2.use_count()<<"] p3.use_count()["<<p3.use_count()<<"]" <<endl; //������ü������return 0;
	
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
�밴���������. . .

*/ 
