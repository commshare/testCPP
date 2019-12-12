#include <iostream>

class A{
	public:
			int a_a ; 
		
	class B{
		public:
			int b_b;
			void change()
			{
				b_b = a_a;
			}
	};
		B b;
   int getBb(){
   	return b.change();
   }
   
};

int main(){
	A a;
	a.a_a = 100;

	std::cout <<" b :"<<a.getBb()<<std::endl; 
}
