
#include<iostream>  
#include<set>  
#include<algorithm>  
#include<vector>  
using namespace std;  


  void worker(const char *caller){
  	printf("caller %s \n",caller);
  }
    void resume() { cout <<"resumed "<<endl;
    //__FUNCTION__ �������resume�����ģ�������� 
  worker (__FUNCTION__);  //��ӡ��ǰ���������� 
   }

  int main(){
 	resume();
  }
  
  
