#include <future>
#include <iostream>
#include <chrono>
void startWorker()
{
   std::future<void> worker;
	//����asyncʱ�������̣߳�ֱ��������future��get����waitʱ�Ŵ����̡߳����ص�Ӧ����std::future��
	//workerû����˭���ð� �����ǿ��std::async�������̣߳���ô�ͱ���ʹ��std::launch::async�����ܵĴ��۾���ϵͳ��Դ����ʱ�����ܳ��������
    worker = std::async(std::launch::async, [] {
        void *tag = NULL;
        bool ok = false;
        static int i = 0;
        while(true)
        {
          std::cout <<"this is async thread "<<std::endl; 
          std::chrono::milliseconds dura(2000); //��һ��5���ʱ��
        	std::this_thread::sleep_for(dura);  //��Ϣһ��ʱ��
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
