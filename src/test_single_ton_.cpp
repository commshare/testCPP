#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class MessageBroker
{
	public:
	MessageBroker(){
		std::cout <<" create mb "<<std::endl;
		
	}
~MessageBroker()
{
	std::cout<<" delete mb "<<std::endl;
}
void dooo()
{
	std::cout <<" dodoodo "<<std::endl;
}
};


	class Impl {
	public:
	  Impl() {
		MSGBOK = make_unique<MessageBroker>();
		if (MSGBOK.get() == nullptr)
		{
		  
		}
		std::cout<<"========end of impl construct "<<std::endl;
	  }
	  ~Impl()
	  {
	  		std::cout<<"========begin of impl DEconstruct "<<std::endl;
	  		//////////����������ص���ѭ��Ӧ���Լ�������������TODO !!!!!!!!!!!!!!!! 
	  		#if 0
		if (instance)
		{
		  delete instance;
		  instance = nullptr;
		}
		#endif
		std::cout<<"========end of impl DEconstruct "<<std::endl;
	  }
	  static Impl* Create()
	  {
		if (instance == nullptr)
		{
		  instance =  new Impl();
		  return instance;
		}
	  }
	  static Impl* get()
	  {
		return instance;
	  }
	  static void Destroy()
	  {
		if (instance)
		{
		  delete instance;
		  instance = nullptr;
		}else{
		
			std::cout <<"cannot delete instance " <<std::endl; 
		}
	  }
	private:
	  static Impl* instance;
	  std::unique_ptr<MessageBroker> MSGBOK;
	};
	
	
		Impl* Impl::instance = nullptr;
		
	int main()
	{
		auto ii =  Impl::Create();
	//	ii->get();
	//�����delete����Դ��Զ�����Զ��ͷ� 
		Impl::Destroy();
		std::cout <<"#########################"<<std::endl;
	}
/*
 create mb
========end of impl construct
========begin of impl DEconstruct
========end of impl DEconstruct  ���캯������֮�������������uniqueָ��  
 delete mb
#########################

--------------------------------
Process exited after 0.02488 seconds with return value 0
�밴���������. . .
*/
