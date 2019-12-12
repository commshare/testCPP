#include <future>
#include <iostream>
#include <chrono>
void startWorker()
{
   std::future<void> worker;
	//调用async时不创建线程，直到调用了future的get或者wait时才创建线程。返回的应该是std::future？
	//worker没看到谁调用啊 如果你强制std::async创建新线程，那么就必须使用std::launch::async，承受的代价就是系统资源紧张时，可能程序崩溃。
    worker = std::async(std::launch::async, [] {
        void *tag = NULL;
        bool ok = false;
        static int i = 0;
        while(true)
        {
          std::cout <<"this is async thread "<<std::endl; 
          std::chrono::milliseconds dura(2000); //定一个5秒的时间
        	std::this_thread::sleep_for(dura);  //休息一定时常
        	i ++;
        	if(i==5)
        	{
        		std::cout <<"exit "<<std::endl;
        		return;
			}

        }
    });
}

int main()
{
	startWorker();
	std::cout <<"after start worker "<<std::endl;
	return 0;
}
