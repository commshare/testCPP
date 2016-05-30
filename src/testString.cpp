#include<iostream>
using namespace std;

int main(){
/*
6	11	J:\media\YY\TESTCPP\testCPP\src\testString.cpp	[Warning] deprecated conversion from string constant to 'char*' [-Wwrite-strings]
*/
	char * p="zhangbin";
	std::string s(p,4);
	cout << s << std::endl;	
	
	return 0;
} 
