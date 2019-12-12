#include <iostream>
#include <atomic>
typedef uint32_t mtk_msgid_t;
#include <atomic>
#define ATOMIC_INT std::atomic<int>
#define ATOMIC_UINT64 std::atomic<unsigned long long>
uint32_t getid()
{
	       ATOMIC_INT msgid_seed_;

  while(true)
   {	
                int32_t expect = msgid_seed_.load();
                int32_t desired = expect + 1;
           
                 std::cout <<"expect £º"<< expect <<std::endl;
                     std::cout <<"(mtk_msgid_t)expect £º"<< (mtk_msgid_t)expect <<std::endl;
             if (atomic_compare_exchange_weak(&msgid_seed_, &expect, desired)) {
                    return (mtk_msgid_t)desired;
                }
                   return 0;
                
   }
	  
}

int main()
{
	     std::cout << "getid()1 " <<getid() <<std::endl;     
	       std::cout << "getid()2 " <<getid() <<std::endl;     
	return 0;
}
