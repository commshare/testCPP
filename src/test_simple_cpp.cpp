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
	Girl g; //�ᴥ��girl�Ĺ�������� 
};

int main(){
	//�����Ϳ��Դ���fc����� b�Ĺ����� 
	Fc fc("zhangbin") ;
	std::cout<<"---AFTER Fc fc ---"<<std::endl;
	std::string name1="hello";
	Fc *pFC= new Fc(name1); 
	std::cout<<"---AFTER Fc *pFC ---"<<std::endl;
	//�����Ϳ����������ˣ��������ڴ�й¶ 
	delete(pFC); 

	
}

/*Ϊɶ���� ֻ��һ���أ���Ϊnew��Ҫdelete�� 
boy constructor  zhangbin
Fc constructor zhangbin
---AFTER Fc fc ---
boy constructor  hello
Fc constructor hello
---AFTER Fc *pFC ---
Fc DEconstructor
boy DEconstructor
*/
