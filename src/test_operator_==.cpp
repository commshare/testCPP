/*
https://github.com/sarnold/cbmc/blob/master/regression/cpp-from-CVS/Overloading_Operators4/main.cpp
*/
#include <stdio.h>
#include <iostream>
struct X {
    X() : i(1),j(2){

    }

    int i;
    int j;

    bool operator == (const struct X &o){
        return i > o.i && j > o.j;
    }
    bool func(){
        X x1,x2;
        x1.i=2;
        return x1 == x2;
    }
};

void doit(){
    X a,b;
    a.i=10;
    a.j=20;
    /*把b带入到==中去*/
    if(a == b ){
        std::cout<<" a == b ";

    }else{
        std::cout<<"a != b" ;
    }
}

int main(){
    doit();
    getchar();
}
