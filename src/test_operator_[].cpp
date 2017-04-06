#include <iostream>
#include <stdio.h>

class C {
    public :
    /*构造函数*/
    C (int _base): base(_base){}

    int operator [] (int x){
        return base + x;
    }

    int operator[] (class Z &z){
        return 0;
    }
    int base;
};

int main(){
    C c(1);

    std::cout<< c[0]<<"should == 1" <<std::endl;
    std::cout<<c[2] <<"should == 3" <<std::endl;
    getchar();
}