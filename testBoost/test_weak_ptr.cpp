
/* boost include folder:
D:\zhangbin\SWA-Server-boost1.60-x64\boost\include 
*/

#include<string>
#include<iostream>
#include<boost/smart_ptr.hpp>
#include<boost/shared_ptr.hpp>

using namespace std;
using namespace boost;
int main(){
	
	
		shared_ptr<int> sp(new int(10));
		assert(sp.use_count() == 1);
		weak_ptr<int> wp(sp);
		assert(sp.use_count() == 1);
		if(!wp.expired()){
			shared_ptr<int> sp2= wp.lock();
			cout<<"1 sp2.count()="<<sp2.use_count()<<endl;
			*sp2=100;
			*sp2=3000;
			cout<<"2 sp2.count()="<<sp2.use_count()<<endl;
			cout<<"*sp2 =" <<*sp2<<endl;
		} 
		
		system("pause");
		return 0;
}

