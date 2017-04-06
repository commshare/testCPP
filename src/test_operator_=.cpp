/*
https://github.com/sarnold/cbmc/blob/master/regression/cpp-from-CVS/Overloading_Operators5/main.cpp
*/

#include <stdio.h>
#include <iostream>

int g;
struct X {
    X(){}

    int i;
    int j;

    X &operator = (const struct X &r);
};

  /*TODO 虽然是返回了一个引用，但貌似并没有给a*/
X &X :: operator = (const struct X &r){
     g=2;
     std::cout << "r.i"<<r.i<<std::endl; /*确实返回的是b的*/
    return * this; /*返回的是引用*/
}

void doit(){
    X a,b;
    a.i=100;
    b.i=200;
    g=1;
    a=b;
    if(g == 2){
        std::cout << "= work"<<std::endl;
    }
    /*TODO 虽然是返回了一个引用，但貌似并没有给a*/
    std::cout << "after a=b ,a.i="<<a.i<<std::endl;
   
}

int main(){
     doit();
     getchar();
     return 0;
}