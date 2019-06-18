#include <thread>
#include <iostream>
class MyThread : public std::thread 
{
	public:
		MyThread() : std::thread()
		{
			
		}
		
		template<typename T, typename ... Args >
		MyThread(T && func, Args && ...args)  :
			std::thread (std::forward<T>(func),
			std::forward<Args> (args) ...) 
			{
			}
		void showcmd( const char *  str)	
		{
			system(str);
		}
};

int main()
{
	MyThread t1( 
	[] ()
	{
		std::cout <<" hello "<<std::endl;
	}
	) ;
	t1.showcmd(" nihao");
	
	MyThread t2(
	[] (const char * str){
		std::cout <<"t2 "<< str <<std::endl;
	},"this is thread "
	);
	t2.showcmd("thread2");
	return 0;
}


