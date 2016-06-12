#include<iostream>
using namespace std;

int main(){
	//左移动是变大啊 ，变成了2*2的三次方 16 
	int i=2<<3;
	cout<<i<<endl;
	
	int j=2>>3;
	cout<<j<<endl; 
	
	//取余 得8 
	cout<<8%i<<endl;
	
	int nn=4<<3;
	cout<<nn<<endl; 
	return 0;
}
