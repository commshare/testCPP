#include<boost/make_shared.hpp>
#include<boost/shared_ptr.hpp>
#include<vector>
#include<iostream>
/*
http://my.oschina.net/lingluonianhua/blog/212533
*/
using namespace std;
int main(){
    /*容器内存储的是shared_ptr*/
    typedef vector<boost::shared_ptr<int> > vs; //一个持有shared_ptr的标准容器类型   
	vs v(10); // //声明一个拥有10个元素的容器，元素被初始化为空指针       
	int i=0;
	for(vs::iterator pos =v.begin(); pos !=v.end(); ++pos){
		/*
		对迭代器pos使用一次解引用操作符*以获得shared_ptr,这个打印出来都是指针 
		*(*pos)也可以直接写成**pos，但前者更清晰，后者很容易让人迷惑
		*/
		(*pos) = boost::make_shared<int>(++i); //使用工厂函数赋值  
		cout<<"*pos["<<*pos<<"] and *(*pos)["<<*(*pos)<<"]"<<endl;
	}
	/*
	vector的operator[]用法与迭代器类似，也需要使用*获取真正的值。
	*/
	boost::shared_ptr<int> p=v[9];
	*p=100;
	cout<<*v[9]<<endl;
	return 0;
}
/*
*pos[0x760d6c] and *(*pos)[1]
*pos[0x760d8c] and *(*pos)[2]
*pos[0x7616bc] and *(*pos)[3]
*pos[0x7616dc] and *(*pos)[4]
*pos[0x7616fc] and *(*pos)[5]
*pos[0x76171c] and *(*pos)[6]
*pos[0x76173c] and *(*pos)[7]
*pos[0x76175c] and *(*pos)[8]
*pos[0x76177c] and *(*pos)[9]
*pos[0x76179c] and *(*pos)[10]
100

--------------------------------
Process exited after 0.01919 seconds with return value 0
请按任意键继续. . .
*/ 
