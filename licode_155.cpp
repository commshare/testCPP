#include <iostream>
#include <cstring>
//https://leetcode-cn.com/problems/min-stack/
/*
���һ��֧�� push��pop��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��

push(x) -- ��Ԫ�� x ����ջ�С�
pop() -- ɾ��ջ����Ԫ�ء�
top() -- ��ȡջ��Ԫ�ء�
getMin() -- ����ջ�е���СԪ�ء�


1. ���ջ��û���޵ģ�����զ�� �Զ�����ѭ�����飿 Ӧ��Ҫ�������ϵ�λ�òŶԣ�ѭ�����Ǹ������ϵ�ô�� 
2. 1��ϵ����ʲô���ݽṹ���������飿
3. ������stlô�� 
*/
#define MAX_SIZE 5 
class MinStack {
	private:
	int cur_;
	int min_;
	int pos_;
	int array[MAX_SIZE]; 
	 int size_;
	 bool first=true; 
	 int last_oper_;
public:
	
    /** initialize your data structure here. */
    MinStack() {
        memset(array,0,MAX_SIZE);
        cur_ = 0;
        size_ = 0;
        //��Сֵ�ǲ��ǲ�Ӧ�ø�ֵ�İ�����һ�ν����Ÿ�ֵ�� 
		//min_ = 0;		 
		pos_ = 0;
    }
    void show()
    {	std::cout <<"--------------"<<std::endl;
    	int i =0;
    	for(;i<MAX_SIZE;i++)
    	{
    		std::cout <<" i "<<i <<" "<< array[i]<<std::endl;
		}
		std::cout <<"------min "<<min_<<std::endl;
			std::cout <<"------size "<<size_<<std::endl;
		std::cout <<std::endl;
	}
	void checkMin(int x)
    {
       if(x < min_)
       {
       	 min_= x;
	   }
	}
	void overwritten(int index)
	{
			//index �ᱻ���� 
		   std::cout <<"--- index will be overwritten "<< index<<std::endl;
	      //����Ҫȥ��index�����indexֵ��min
	      if(array[index ] == min_)		  
		  {
		  	 //���ʱ��ͨ��������ȡ��Сֵ,������Сֵ���ǳ�������λ������Ԫ�ص���Сֵ�� 
			 	int i =0;
			 	//�պ�index���ǵ�һ��Ԫ�أ������Ͳ�׼ȷ�� ������һֱ���ǣ����Ƿ��ص�����ʷ�ϵ���Сֵ�������� 
			 	if(index == 0)
			 	{
			 		i ++;
				}
    			min_ = array[i];
    			std::cout <<"--- reset min to "<< min_<<std::endl;
    			for(;i<size_;i++)
    			{
    			   if(i != index)				   
				   {
				   	 checkMin(array[i]); 
				   }	    			  
				}   
		  } 
	} 
    void push(int x) {
    	std::cout <<"---push "<<x<<std::endl;
       if(first)
       {
       	min_ = x;
       	first = false;
	   }
    	//ʵ�ʲ���λ�� ��index 
       int index = pos_ % MAX_SIZE ;
       //����һ�� 
       size_ ++ ;
       //������������������������˵�����Ҫ����һ���Ѿ��е� 
       if(size_ > MAX_SIZE)
       {
       	  //����֮��������ֵ 
		   size_ =  MAX_SIZE;
           overwritten(index);
	   }
       //���µ�max��Ԫ�ص���Сֵ 
	   checkMin(x); 
	   //���� 
	   array[index] = x;
	   //��ǰԪ��λ�ã���ս�� 
	   cur_ = index; 
	    //�ȴ��´β��� 
        pos_ = pos_ + 1; 

	   show();
    }
    
    void pop() {
    	//����Ҫ���أ�ֱ�Ӹ��ǰ� 
        //pop֮�����cur_λ�ò��� 
        pos_ = cur_; 
        overwritten(cur_);
        std::cout <<" --------  pop "<<array[cur_] <<std::endl; 
        //�������� ���س�ջ֮�����һ��Ԫ��λ�� ��		 
        cur_ = (cur_ -1 ) % MAX_SIZE;
        size_ --;
        show();
    }
    
    int top() {
    	   std::cout <<"-------- top "<<array[cur_] <<std::endl; 
    	     show();
        return array[cur_];
    }
    
    int getMin() {
    	  show();
    	  #if 0 
    	  //����Ҳ���У���Ϊ�е�û�����ݲ��룬�������ˡ� 
    	//��ȡ����һ�飬������MAX��Ԫ��  
    	int i =0;
    	min_ = array[i];
    	for(;i<MAX_SIZE;i++)
    	{
    	   checkMin(array[i]); 
		}
		#endif 
        return min_;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
 void push( MinStack* obj ,int x)
 {
 	std::cout <<" push "<<x <<std::endl; 
             obj->push(x);
 }
 int main()
 {
 	  MinStack* obj = new MinStack();
#if 1
 	  push(obj,10);
 	  push(obj,20);
  	  push(obj,30);
  	  push(obj,40);
  	  push(obj,50);
  	  push(obj,60);
  	  push(obj,70);
  	  push(obj,80);
      //std::cout <<" pop " <<std::endl; 
      obj->pop();
  
      int param_3 = obj->top();
      int param_4 = obj->getMin();
      std::cout <<" top "<<param_3 <<" min "<< param_4 <<std::endl; 
       obj->pop();
  	    obj->top();
  	    
	 #else
	   push(obj,-2);
 	  push(obj,0);
  	  push(obj,-3);
  	    obj->pop();
  	    obj->top();
	 #endif 
      if(obj)
      {
      	delete obj;
      	obj = nullptr;
	  }
 	  return 0;
 	
 }
