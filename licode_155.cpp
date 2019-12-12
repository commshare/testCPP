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
        //最小值是不是不应该赋值的啊，第一次进来才赋值的 
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
			//index 会被覆盖 
		   std::cout <<"--- index will be overwritten "<< index<<std::endl;
	      //所以要去掉index，如果index值是min
	      if(array[index ] == min_)		  
		  {
		  	 //这个时候通过遍历获取最小值,这样最小值就是除掉覆盖位置其他元素的最小值了 
			 	int i =0;
			 	//刚好index就是第一个元素，这样就不准确了 ，或者一直覆盖，但是返回的是历史上的最小值？？？？ 
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
    	//实际插入位置 是index 
       int index = pos_ % MAX_SIZE ;
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
        pos_ = cur_; 
        overwritten(cur_);
        std::cout <<" --------  pop "<<array[cur_] <<std::endl; 
        //这样来？ 返回出栈之后的上一个元素位置 ？		 
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
    	  //这样也不行，因为有的没有数据插入，就乱码了。 
    	//获取遍历一遍，反正就MAX个元素  
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
