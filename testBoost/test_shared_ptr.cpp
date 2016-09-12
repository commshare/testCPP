#include<string>
#include<iostream>
#include<boost/shared_ptr.hpp>
/*http://www.cnblogs.com/TianFang/archive/2008/09/19/1294521.html
boost::scoped_ptr��Ȼ�����ã��������ܹ�������Ȩ������ȴ�����������ʹ�÷�Χ����
boost::shared_ptr���Խ����һ���ޡ�����˼�壬boost::shared_ptr�ǿ��Թ�������Ȩ������ָ�룬����������ͨ��һ�����ӿ������Ļ����÷���

http://blog.csdn.net/jnu_simba/article/details/9569593 more info ...

*/
using namespace std;
class impl{
	public :
		~impl(){
			cout<<"destroy impl "<<endl;
		}
		void do_sth(){
			cout<<"do sth"<<endl;
		}

};

		void test(){
			boost::shared_ptr<impl> sp1(new impl()); //sp1��implementation������й��������ü���Ϊ1 
			cout<<"sp1 reference count"<<sp1.use_count()<<endl;
			boost::shared_ptr<impl> sp2= sp1; //����sp2��implementation������й��������ü�������Ϊ2 
			cout<<"now ,sp2 refernce count "<<sp2.use_count()<<endl;
			
			sp1.reset(); //sp1�ͷŶ�implementation������й��������ü�����Ϊ1 
			cout<<"after reset sp1 , sp2 reference count"<<sp2.use_count()<<endl;
			sp2.reset(); //sp2�ͷŶ�implementation������й��������ü�����Ϊ0���ö����Զ�ɾ�� 
			cout<<"reset sp2 ,sp2 count"<<sp2.use_count()<<"sp1 count " <<sp1.use_count()<<endl;
			
						
		}
		
		
int main(){
	test();
	

	return 0;
}
/*
sp1 reference count1
now ,sp2 refernce count 2
after reset sp1 , sp2 reference count1
destroy impl
reset sp2 ,sp2 count0sp1 count 0

--------------------------------
Process exited after 0.01472 seconds with return value 0
�밴���������. . .
*/
