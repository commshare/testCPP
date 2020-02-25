#include <stdlib.h>
#include <iostream>

using namespace std;
//https://github.com/begeekmyfriend/leetcode-1/blob/master/algorithms/cpp/minStack/minStack.cpp
//It seems C++ vector cause the Memory Limit Error, So, implement a simple one
template <typename T>
class Stack{
private:
T * stack_;
int capacity;
int top_;
public:
Stack():capabilty_(1),top_(-1) {
    stack_ = (T*) malloc(capablity_ *sizeof(T));
}
~Stack(){
    free(stack_);
}
void push(T x)
{
    top_ ++;
    if(top_>= capability_){
         //if capacity is not enough, enlarge it 5 times.
         //Notes: why 5 times? because if you change to other(e.g. 2 times), 
        //       LeetCode system will report Run-time Error! it sucks!
        capability *= 5;
        stack_ = (T*)realloc(stack_ , capability *sizeof(T));
    }
    stack_[top] = x;
}
T pop(){
    return top(true);
}
T &top(bool pop= false){
    if(top_> 0){
        if(pop){
            return stack_[top_ --];
        }
        return stack_[top_];
    }
    static T null;
    return null;
}
bool empty()
{
    return (top_ < 0 );
}
int size()
{
    return top_ + 1;
}
void clear()
{
    top_ = -1;
}
};


 
 /*
 * Idea: 
 *
 *    Using two stacks, 
 *    1) one stack is the real stack to store the data.
 *    2) another stack store the minimal number when it changes.
 *
 *    For example:
 *
 *        if we keep pushing the following numbers:
 *        5 1 1 2 3 2 
 *        the minial number stack will be: 
 *        5 1 1   <-- only store the number which <= cureent minimal number
 *   
 *    Then, when we pop up the stack.
 *
 *    we need compare whether the current number is the current minial number.
 *    if it is, then we need popup the number in minimal number stack.
 *        
 */
 
 class MinStack{
     private:
        //Using a minData struct to remove the duplication in minimal stack
        //which can save the memory.
     struct minData{
         int min_;
         int cnt_;
         minData : min_(0),cnt_(0){
         }
         minData(int m ,int c):min_(m),cnt_(c) {} ;
     };  
     Stack<int> stack_;//real stack store the data
     Stack<minData> minStack_; // mini stack store the number
     int min_; // current minial number
public:
    void push(int x){
        if(stack_.empty())
        {
            min_ = x;
            minStack_.push(minData(x,1));
        
        }else{
            if(min_ >= x)
            {
                min_ = x;
                //if current minial number already pushed ,then just add  the reference count
                if(minStack_.top().min_ == x)
                {
                    minStack_.top().cnt_ ++;
                }else{
                    minStack_.push(minData(x,1));
                }
            }
        }
        stack_.push(x);
    }
    void pop(){
        if(stack_.empty())
        {
            return;
        }
        int x=stack_.pop();
        if(x == minStack_.top().min_){
            //de-reference the count at first
            if(minStack_.top().cnt_ >1)
            {
                minStack_.pop();
                min_ = minStack_.top().min_;
            }else{
                minStack_.pop();
                min_ = minStack.top().min_;
            }
        }
    }
    int top(){
        return stack_.top();
    }
    int getMin(){
        return min_;
    }

    void clear(){
        stack_.clear();
        minStack_.clear();
    }
 };

 int main()
{
    cout << "--- expected output [0, 0, 0, 2]" << endl;
    MinStack ms;
    ms.push(2);
    ms.push(0);
    ms.push(3);
    ms.push(0);

    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;


    ms.clear();

    cout << "--- expected output [2147483647 2147483646 2147483646 2147483647 2147483647 -2147483648 -2147483648 2147483647 " << endl;

    ms.push(2147483646);
    ms.push(2147483646);
    ms.push(2147483647);

    cout << ms.top() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();

    ms.push(2147483647);
    cout << ms.top() << endl;
    cout << ms.getMin() << endl;
    ms.push(-2147483648);
    cout << ms.top() << endl;
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;


    return 0;
}