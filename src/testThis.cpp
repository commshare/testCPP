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
	///���this�ǲ����ó�Ա�����Ķ���ĵ�ַ���������Ƕ���a1�ĵ�ַ
	if(this == &aa){ /*this is the address of aa*/
		cout<<"no need to copy" <<endl;
		return;
	}
	/*
	 //*this�ǲ����ó�Ա�����Ķ����������Ƕ���a1��
     //������Ƕ���aa����a1��Ҳ����aa���е����ݳ�Ա��ֵ����a1�����ݳ�Ա
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
