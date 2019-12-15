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
//#define MAX_SIZE 5 
class MinStack {
	private:
		static const int MAX_SIZE = 5;
	int cur_;
	int min_;
	int pos_;
	int array[MAX_SIZE]; 
	 int size_;
	 bool first=true; 
	 int last_oper_;
	 int tag_array_[MAX_SIZE]; //��0��1 ,1�����index��Ч 
public:
	
    /** initialize your data structure here. */
    MinStack() {
        memset(array,0,MAX_SIZE);
        cur_ = 0;
        size_ = 0;
        //��Сֵ�ǲ��ǲ�Ӧ�ø�ֵ�İ�����һ�ν����Ÿ�ֵ�� 
		//min_ = 0;		 
		pos_ = 0;
		memset(tag_array_,0,MAX_SIZE);
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
		   std::cout <<"--- index  "<< index<<std::endl;
		   //����һ��bug��ȫ��pop��ϵ� ʱ�򣬲�Ӧ����minֵ����������ҵ�ֻ��pop���߸���ʱmin���� ������߼��ʹ��ˣ�����min����Ҫÿ�ζ������ſ��� 
		   #if 0 
	      //����Ҫȥ��index�����indexֵ��min
	     // if(array[index ] == min_)		  
		  {
		  	  std::cout <<"			 index "<<index <<" is min ��overwritten  "<< min_<<std::endl;
		  	 //���ʱ��ͨ��������ȡ��Сֵ,������Сֵ���ǳ�������λ������Ԫ�ص���Сֵ�� 
		  	 //��ͷ��ʼ 
			 	int i =0;
    			if(i == index)
    			{
    				i++;
				}
				//��minΪ��ͷ��ֵ 
				min_ = array[i];
				//�� ��ʼ��i��ʼ�Ƚ�			 
    			for(;i<MAX_SIZE;i++)
    			{
    				
    			   if(i != index && tag_array_[i]==1)				   
				   {
				   	 checkMin(array[i]); 
				   }	    			  
				}   
				std::cout <<"			--- reset min to "<< min_<<std::endl;
		  } else
		  {
		  		std::cout <<"			---no need to  reset min to "<< min_<<std::endl;
		  }
		  #endif
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
       tag_array_[index] =1;
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
        std::cout <<"   ----pop-- begin"<<min_<<std::endl;
        pos_ = cur_;  
        std::cout <<"   ---out pop "<<array[cur_] <<" cur_ "<<cur_ <<std::endl; 
        
        //����Ϊ�����ã� 
        tag_array_[cur_]=0;
        
        overwritten(cur_);
     
        //�������� ���س�ջ֮�����һ��Ԫ��λ�� ��		 
        cur_ = (cur_ -1 ) % MAX_SIZE;
        size_ --;
    
        show();
        std::cout <<"  ----pop--end set cur_"<<cur_<<std::endl;
    }
    
    int top() {
    	std::cout <<" top "<<array[cur_]<<" cur_ "<<cur_ <<std::endl; 
    	show();
        return array[cur_];
    }
    
    int getMin() {
    	//show();
    			int i =0;
    		    bool use_first_valid=true;
			
			
				//�� ��ʼ��i��ʼ�Ƚ�			 
    			for(;i<MAX_SIZE;i++)
    			{
    			   if(tag_array_[i]==1)				   
				   {
				   	//ʹ�õ�һ����Чֵ��Ϊmin�ĳ�ʼֵ 
				   	if(use_first_valid)
				   	{
					   	min_ = array[i];
					   	use_first_valid=false;
					}
				   	 checkMin(array[i]); 
				   }	    			  
				}   
				std::cout <<"			--- reset min to "<< min_<<std::endl;
    		std::cout <<"getMin--min "<<min_<<std::endl;
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
 void push( MinStack* obj ,int x,int step)
 {
    	std::cout <<"step "<<step<<" push "<<x <<std::endl; 
             obj->push(x);
 }
  void pop( MinStack* obj ,int step)
 {
      
      std::cout <<"step "<<step<<" pop " <<std::endl; 
      obj->pop();

 }
   void min( MinStack* obj ,int step)
 {
      int x=       obj->getMin(); 
      std::cout <<"step "<<step<<" getmin "<<x <<std::endl; 

 }
    void top( MinStack* obj ,int step)
 {
      int x=       obj->top(); 
      std::cout <<"step "<<step<<" top "<<x <<std::endl; 

 }
 int main()
 {
 	  MinStack* obj = new MinStack();
#if 0
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
	 #if 0 
	   push(obj,-2);
 	  push(obj,0);
  	  push(obj,-3);
  	  obj->getMin(); //  --> ���� -3.
  	  obj->pop();
  	    obj->top();
  	    obj->getMin(); //  --> ���� -3.
  	    #else
  	   push(obj,2147483646,1); //1
	   push(obj,2147483646,2);//2
	   push(obj,2147483647,3);//3
  top(obj,4);//4
       pop(obj,5);//5
       min(obj,6); //6
       pop(obj,7);//7
       min(obj,8); //8

       pop(obj,9);//9

  	    	   push(obj,2147483647,10); //10
top(obj,11);//11
  min(obj,12); //12
	   push(obj, -2147483648,13);//13
top(obj,14);//14
          min(obj,15); //15
 pop(obj,16);//16
             min(obj,17); //17

  	    #endif
	 #endif 
      if(obj)
      {
      	delete obj;
      	obj = nullptr;
	  }
 	  return 0;
 	
 }
