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
	 int last_index_; 
public:
	
    /** initialize your data structure here. */
    MinStack() {
        memset(array,0,MAX_SIZE);
        cur_ = 0;
        size_ = 0;
        last_index_ =0;
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
		std::cout <<"------min "<<getMin()<<std::endl;
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
          // overwritten(index);
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

        std::cout <<"   ----pop-- begin min "<<min_ <<" cur_ "<< cur_ <<" out pop "<<array[cur_]<<std::endl;
        
        //先置为不可用？ 
        tag_array_[cur_]=0;
        
       // overwritten(cur_);
       //计算cur位置，也就是出栈之后，如果要top该用哪个值 
       //有可能此时栈空了，那么cur应该是那个？如 
         size_ --;
         //这样来？ 返回出栈之后的上一个元素位置 ？	
		if( cur_ ==0)
		{
			if(size_ == 0 )
			{
				//没元素了，就在0位置 ，这个时候，top应该返回错误 
				cur_ = 0;
			}
			else
		    {
		    	//还有元素，上一个位置是哪里？ 
		    		cur_ = MAX_SIZE -1; 
		    
			 } 
		}else
		{
			// cur为0，算出来是-1啊 TODO ,上面的判断就是为了修复这个问题 
			  cur_ = (cur_ -1 ) % MAX_SIZE;
		}

        std::cout<<"    pop ok  former  "<< pos_ <<" cur_ " << cur_ <<std::endl;
       
    
        show();
       // std::cout <<"  ----pop--end set cur_"<<cur_<<std::endl;
    }
    
    //没有元素的时候，要返回什么？abort？ 
    int top() {
    	if(size_ ==0)
		{
			std::cout <<"!!!! size is 0 no top " <<std::endl; 
		 abort(); 
		 } 
    	std::cout <<" top begin : value "<<array[cur_]<<" will top out , cur_ "<<cur_ <<std::endl; 
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
			//	std::cout <<"			--- reset min to "<< min_<<std::endl;
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
 void test11(MinStack* obj)
 {
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
 }
 void test12(MinStack* obj)
 {
 	 	  push(obj,2,1);
 	 	  push(obj,0,2);
 	 	   	 	  push(obj,3,3);
 	 	   	 	   	 	  push(obj,0,4);
 	 	   	 	   	 	  min(obj,5);
 	 	   	 	   	 	  pop(obj,6);
 	 	   	 	   	 	   min(obj,7);
 	 	   	 	   	 	  pop(obj,8);




 }
 void test9(MinStack* obj)
 {
 	 push(obj,2,1);
 	   push(obj,0,2);
 	     push(obj,3,3);
 	      min(obj,4);
 	      	 push(obj,0,5);
 	      	  	      min(obj,6);
 	      	  	       pop(obj,7);
 	      	  	        min(obj,8);
 	      	  	         pop(obj,9);

 	     min(obj,10);
 }
 
 void test13(MinStack* obj)
 {
 	 push(obj,85,1);
 	   push(obj,-99,2);
 	     push(obj,67,3);
 	      min(obj,4);
 	       push(obj,-27,5);
 	   push(obj,61,6);
 	     push(obj,-97,7);
 	      push(obj,-27,8);
 	   push(obj,35,9);
 	    top(obj,10);
 	    push(obj,99,11);
 	   push(obj,-66,12);
 	     min(obj,13);
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
  	  test13(obj);

  	    #endif
	 #endif 
      if(obj)
      {
      	delete obj;
      	obj = nullptr;
	  }
 	  return 0;
 	
 }
