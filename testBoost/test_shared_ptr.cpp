#include<string>
#include<iostream>
#include<boost/shared_ptr.hpp>
/*http://www.cnblogs.com/TianFang/archive/2008/09/19/1294521.html
boost::scoped_ptr虽然简单易用，但它不能共享所有权的特性却大大限制了其使用范围，而
boost::shared_ptr可以解决这一局限。顾名思义，boost::shared_ptr是可以共享所有权的智能指针，首先让我们通过一个例子看看它的基本用法：

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
			boost::shared_ptr<impl> sp1(new impl()); //sp1对implementation对象进行管理，其引用计数为1 
			cout<<"sp1 reference count"<<sp1.use_count()<<endl;
			boost::shared_ptr<impl> sp2= sp1; //增加sp2对implementation对象进行管理，其引用计数增加为2 
			cout<<"now ,sp2 refernce count "<<sp2.use_count()<<endl;
			
			sp1.reset(); //sp1释放对implementation对象进行管理，其引用计数变为1 
			cout<<"after reset sp1 , sp2 reference count"<<sp2.use_count()<<endl;
			sp2.reset(); //sp2释放对implementation对象进行管理，其引用计数变为0，该对象被自动删除 
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
请按任意键继续. . .
*/
