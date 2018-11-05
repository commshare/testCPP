#include <iostream>
#include <vector> 
class Boy{
	public :
	 Boy(std::string name){
		std::cout <<"boy constructor  "<<name<< std::endl;
	}
	 ~Boy(){
			std::cout <<"boy DEconstructor "<< std::endl;
	}
};
class Girl{
	public :
	 Girl(){
		std::cout <<"Girl constructor  "<< std::endl;
	}
	 ~Girl(){
			std::cout <<"Girl DEconstructor "<< std::endl;
	}
};
class Fc {
	public :
	 Fc(std::string name ):b(name){
		std::cout <<"Fc constructor "<< name<<std::endl;
	}
	 ~Fc(){
			std::cout <<"Fc DEconstructor "<< std::endl;
	}
	Boy b;
	Girl g; //会触发girl的构造和析构 
};

int main(){
	//这样就可以触发fc构造和 b的构造了 
	Fc fc("zhangbin") ;
	std::cout<<"---AFTER Fc fc ---"<<std::endl;
	std::string name1="hello";
	Fc *pFC= new Fc(name1); 
	std::cout<<"---AFTER Fc *pFC ---"<<std::endl;
	//这样就可以析构掉了，不会有内存泄露 
	delete(pFC); 

	
}

/*为啥析构 只有一次呢，因为new的要delete掉 
boy constructor  zhangbin
Fc constructor zhangbin
---AFTER Fc fc ---
boy constructor  hello
Fc constructor hello
---AFTER Fc *pFC ---
Fc DEconstructor
boy DEconstructor
*/
