
/*
https://github.com/sarnold/cbmc/blob/master/regression/cpp-from-CVS/Overloading_Operators1/main.cpp
*/
#include<iostream>
#include<stdio.h>
class T{
    public :
};

int operator+(T a,int b){
    return b;
}

int operator-(T a,int b){

    return -b;
}

int main(){
    T x ;
    int temp;
    temp= x + 2;
    std::cout<< temp <<std::endl;

    temp = x - 3;
    std::cout<< temp<<std::endl;
    getchar ();
}