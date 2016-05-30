/*
http://www.cnblogs.com/lihuidashen/p/4383038.html
*/
#include<iostream>
using namespace std;

class A{
	public :
		A() {
			a=b=0;
		}
		A(int i, int j){
			a=i;
			b=j;
		}
		//pass reference 
		void copy(A &aa);
		void print(){cout << a << ","<<b<<endl; 
		}
		private :
			int a,b;
		
};

void A::copy (A &aa){
	///这个this是操作该成员函数的对象的地址，在这里是对象a1的地址
	if(this == &aa){ /*this is the address of aa*/
		cout<<"no need to copy" <<endl;
		return;
	}
	/*
	 //*this是操作该成员函数的对象，在这里是对象a1。
     //此语句是对象aa赋给a1，也就是aa具有的数据成员的值赋给a1的数据成员
	*/
	*this=aa;
}


int main(){
	A a1,a2(3,4);
	//pass a2's refernce to function
	a1.copy(a2);
	a1.print();
	return 0;
}
