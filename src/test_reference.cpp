#include <iostream>
#include <cstdio>
using namespace std;

struct Frame{
    std::string frame;
};
class Test{

    public :
      void  passData(string &data);
      void showData(){
          cout<< "the data: " << myframe.frame <<std::endl;
      }
    private:
        Frame myframe;
};




/*传递一个引用过来，赋值给一个非指针的成员*/
void Test::passData(string &data){
    myframe.frame = data;
}
// 写一个返回string的函数(函数返回局部变量string的时候能不能被引用？)
// 实际上返回的不是局部变量，而是编译器新构造的临时对象。
std::string TestStringReference()
{
    std::string strTest = "This is a test.";
    return strTest;
}


int main(){
    Test t;
    std::string data= "zhangbin";
    // 这里要传递 data，而不是 &data，
    t.passData(data);
    t.showData();
    
    // 返回的变量被引用,返回的“局部”string可以被引用的，实际上返回的不是局部变量，而是编译器新构造的临时对象。
    //这个返回的引用必需是一个const类型的，否则c++会报错的
    const std::string& strRefer = TestStringReference();
    std::cout << "strRefer:" << strRefer << std::endl;

    //http://blog.csdn.net/wangshubo1989/article/details/50286985
    // 先用一个string接收函数的返回值，然后再调用c_str()方法： 貌似直接返回一个对临时对象的指针之后，这个指针指向的临时对象就会销毁
     std::string str1 = TestStringReference();
     const char *pc = str1.c_str();
    std::cout << pc << std::endl;
    getchar();
    return 0;
}