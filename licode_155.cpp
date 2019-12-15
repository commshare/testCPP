#include <iostream>
#include <cstring>
//https://leetcode-cn.com/problems/min-stack/
/*
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) -- 将元素 x 推入栈中。
pop() -- 删除栈顶的元素。
top() -- 获取栈顶元素。
getMin() -- 检索栈中的最小元素。


1. 这个栈有没上限的，满了咋办 自动采用循环数组？ 应该要覆盖最老的位置才对，循环的是覆盖最老的么？ 
2. 1关系到用什么数据结构，比如数组？
3. 可以用stl么？ 
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
	 int tag_array_[MAX_SIZE]; //就0和1 ,1代表该index有效 
public:
	
    /** initialize your data structure here. */
    MinStack() {
        memset(array,0,MAX_SIZE);
        cur_ = 0;
        size_ = 0;
        //最小值是不是不应该赋值的啊，第一次进来才赋值的 
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
			//index 会被覆盖 
		   std::cout <<"--- index  "<< index<<std::endl;
		   //出现一个bug，全部pop完毕的 时候，不应该有min值，如果按照我的只有pop或者覆盖时min命中 ，这个逻辑就错了，所以min还是要每次都遍历才靠谱 
		   #if 0 
	      //所以要去掉index，如果index值是min
	     // if(array[index ] == min_)		  
		  {
		  	  std::cout <<"			 index "<<index <<" is min ，overwritten  "<< min_<<std::endl;
		  	 //这个时候通过遍历获取最小值,这样最小值就是除掉覆盖位置其他元素的最小值了 
		  	 //从头开始 
			 	int i =0;
    			if(i == index)
    			{
    				i++;
				}
				//重min为开头的值 
				min_ = array[i];
				//从 开始的i开始比较			 
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
    	//实际插入位置 是index 
       int index = pos_ % MAX_SIZE ;
       tag_array_[index] =1;
       //新增一个 
       size_ ++ ;
       //新增的这个超过了最大数量，说明这个要覆盖一个已经有的 
       if(size_ > MAX_SIZE)
       {
       	  //覆盖之后就是最大值 
		   size_ =  MAX_SIZE;
           overwritten(index);
	   }
       //最新的max个元素的最小值 
	   checkMin(x); 
	   //覆盖 
	   array[index] = x;
	   //当前元素位置，出战用 
	   cur_ = index; 
	    //等待下次插入 
        pos_ = pos_ + 1; 

	   show();
    }
    
    void pop() {
    	//不需要返回，直接覆盖吧 
        //pop之后就在cur_位置插入 
        std::cout <<"   ----pop-- begin"<<min_<<std::endl;
        pos_ = cur_;  
        std::cout <<"   ---out pop "<<array[cur_] <<" cur_ "<<cur_ <<std::endl; 
        
        //先置为不可用？ 
        tag_array_[cur_]=0;
        
        overwritten(cur_);
     
        //这样来？ 返回出栈之后的上一个元素位置 ？		 
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
			
			
				//从 开始的i开始比较			 
    			for(;i<MAX_SIZE;i++)
    			{
    			   if(tag_array_[i]==1)				   
				   {
				   	//使用第一个有效值作为min的初始值 
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
  	  obj->getMin(); //  --> 返回 -3.
  	  obj->pop();
  	    obj->top();
  	    obj->getMin(); //  --> 返回 -3.
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
