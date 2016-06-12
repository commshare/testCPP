//http://liam2199.blog.51cto.com/2879872/1426780

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> INTVEC;

/*
vector 's display fucntion
void showVec(const INTVEC &v){
	unsinged int i=0;
	for( i=0 ; i< v.size ; ++i){
		cout<< v[i] <<" "<<endl;
	}
	cout<<endl;	
}
*/
/*
show the vector by iterator
*/

void showVec(const INTVEC &v){
	//* it 不能复制，不能改写内容 
	INTVEC::const_iterator it;
	for(it = v.begin() ; it!= v.end(); ++it){
		cout << *it <<" ";
	} 
	cout<<endl;
}

void testRef(int &m){

	cout<<"set m["<<m<<"to new value 999"<<endl;
	
	m=999;
}

/*
insert() 插入元素到Vector中

  iterator insert( iterator loc, const TYPE &val );                      //在指定位置loc前插入值为val的元素,返回指向这个元素的迭代器
  void insert( iterator loc, size_type num, const TYPE &val );  //在指定位置loc前插入num个值为val的元素 
  void insert( iterator loc, input_iterator start, input_iterator end ); //在指定位置loc前插入区间[start, end)的所有元素

*/ 

/*
should not use const INTVEC
47	22	J:\media\YY\TESTCPP\testCPP\src\testVector1.cpp	[Error] no matching function for call to 'std::vector<int>::insert(std::vector<int>::const_iterator, int&) const'
*/
void insertFront(INTVEC &v,int m){
	if(v.empty()) {
		cout<<"vector is empty" <<endl;
		return ;
	}
	v.insert(v.begin(),m);
}
void insertTail(INTVEC &v,int m){
	if(v.empty()) {
		cout<<"vector is empty" <<endl;
		return ;
	}
	v.insert(v.end(),m);
}
int main(void){
	INTVEC v;
	/*从vector的尾部插入*/
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
		v.push_back(5);
	cout<<"show cur  element " ;
	//pass ref of v
	showVec(v);
	cout<<"print the last element "<<v.back() <<endl;
	
	/*从vector尾部弹出*/ 
	cout << "pop the last one "<<endl;
	v.pop_back();
	cout<<endl;
	
	cout<<"show cur elements"<<endl;
	showVec(v);
	
	cout<<"erase element "<<endl;
	v.erase(v.begin()+2);
 	cout<<"show cur elements"<<endl;
	showVec(v);
	
	 
	
	
	int m=33;
	testRef(m);
	cout<<"after set value to ref of m["<<m<<"]"<<endl;
	
	
	cout<<"insert to beginning "<<endl;
	insertFront(v,100);
	insertTail(v,99);
	 	cout<<"show cur elements"<<endl;
	showVec(v);
	
	return 0; 
}
