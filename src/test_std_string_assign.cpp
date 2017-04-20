/*
如何在VSCode内编译运行C++？
http://www.jianshu.com/p/d0350f51e87a
*/

#include<string>  
#include<iostream>  
#include <cstdio>

using namespace std;  
main()  
{  
string s("12345asdf");  
string a=s.substr(0,4);    //获得字符串s中 从第0位开始的长度为4的字符串  
cout<<a<<endl;  


string str1, str2 = "War and Peace";  
str1.assign( str2, 4, 3 );   
//str2 字符串的第4个字符位置开始赋值给str1，长度为3个字符  
cout << str1 << endl;  

getchar();
}  