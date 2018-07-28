
#include<iostream>  
#include<set>  
#include<algorithm>  
#include<vector>  
using namespace std;  


  void worker(const char *caller){
  	printf("caller %s \n",caller);
  }
    void resume() { cout <<"resumed "<<endl;
    //__FUNCTION__ 这个就是resume函数的，这个名字 
  worker (__FUNCTION__);  //打印当前函数的名字 
   }

  int main(){
 	resume();
  }
  
  
