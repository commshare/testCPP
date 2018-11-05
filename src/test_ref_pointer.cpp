
#include<iostream>  
#include<set>  
#include<algorithm>  
#include<vector>  
using namespace std;  

int get(int index, int * pointer=NULL){
	index = -1;
	*pointer = 100 ;
	return (index + *pointer );
}

int main(){
	int m = 44;
	int *p = &m;

		cout <<"m " <<m<<endl;
			int n = get(3,p);
	cout <<"*p "<<*p<<endl;
	cout <<"m " <<m<<endl;
	cout <<"n :" <<n <<endl;
}
