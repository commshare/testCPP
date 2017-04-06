#include <cassert>
#include<stdio.h>
#include <iostream>
/*
http://stackoverflow.com/questions/2909059/assert-was-not-declared-in-this-scope-in-mysql
*/

/*
https://github.com/sarnold/cbmc/blob/c7bdeb8e654651afcd0fef987b4d4887bf9e46ba/regression/cpp-from-CVS/Overloading_Operators10/main.cpp
*/

struct A{
    bool True() {return true;}
};

struct B{
    A a;
    A * operator->() {
        return &a;
    }
};

struct C {
    B b;
    B& operator->() {
        return b;
    }
};


int main(){
    C c;
    if(c->True()==true){
        std::cout<<"true";
    }
    assert(c->True());
    getchar();
}