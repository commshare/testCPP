/*************************************************************************
	> File Name: testRef.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年09月02日 星期三 10时32分26秒
 ************************************************************************/

#include<iostream>
using namespace std;
//nclude <iostream.h>
float temp;//定义全局变量temp
float fn1(float r);/*声明函数fn1*/
float &fn2(float r);/*声明函数fn2*/
float fn1(float r) /*return global temp by  value */
{
    temp=(float)(r*r*3.14);
    return temp;
}

float &fn2(float r) /*return by reference*/
{
    temp=(float)(r*r*3.14);
    return temp;
}

int main(){
    /*
    第1种情况，系统生成要返回值的副本（即临时变量）
    */
    float a=fn1(10.0);
    /*
    第2种情况，可能会出错（不同 C++系统有不同规定）
    不能从被调函数中返回一个临时变量或局部变量的引用
    g++ error :
    testRef.cpp:35:22: 错误：用类型为‘float’的右值初始化类型为‘float&’的非常量引用无效
     float &b=fn1(10.0);

    */
   // float &b=fn1(10.0);

    /*
    //第3种情况，系统不生成返回值的副本
    可以从被调函数中返回一个全局变量的引用
    */
    float c=fn2(10.0);
    /*
    //第4种情况，系统不生成返回值的副本
　//可以从被调函数中返回一个全局变量的引用
    */
    float &d=fn2(10.0);
    cout << a  <<endl <<endl << c <<endl<< d <<endl;
    return 0;
}
