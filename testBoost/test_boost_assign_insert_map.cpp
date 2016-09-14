#include<boost/assign/list_inserter.hpp> //for insert()
#include<boost/assert.hpp>
#include<string>
#include<map> //for map

#include<iostream>


using namespace std;
using namespace boost::assign ; //bring insert() into scope

template<typename T> 
void printMap(T& cb){
	for(auto& x: cb){
		cout<<x<<";" ;
	}
}

typedef map<string , int > myMap;

int printMap2(myMap& cb){
	for(auto& x: cb){
		cout<<x.first <<" has value "<<x.second<<";" ;
	}
	cout<<"----"<<endl;
	return 0;
}
int main(){

//使用insert()等函数进行插入

	map<string,int> months;
	insert(months) 
	("january",31) ("february",28)
	 ( "march",     31 )( "april",    30 )    
        ( "may",       31 )( "june",     30 )    
        ( "july",      31 )( "august",   31 )    
        ( "september", 30 )( "october",  31 )    
        ( "november",  30 )( "december", 31 );    
        
        BOOST_ASSERT(months.size() == 12);
        BOOST_ASSERT(months["january"] == 31);


printMap2(months);

/*auto &x是一个map类型的引用*/ 
for(auto &x: months){
	cout<<x.first<<" has value "<<x.second<<endl;
}
cout<<"====="<<endl;


for(auto x: months){
	cout<<x.first<<" has value "<<x.second<<endl;
}
cout<<"====="<<endl;

/* 迭代器 ，是一个指针*/
for(auto it=begin(months);it!=end(months);++it){
	cout<<it->first<<" has value "<<it->second<<endl;
}
system("pause");
return 0;
}
