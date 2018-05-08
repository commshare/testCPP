#include<iostream>
#include<vector>
using namespace std;

enum ISPType 
{
  AUTO_DETECT  = 0,
  CTL          = 1,   // China Telecom 
  CNC          = 2,   // China Netcome (China Unicom) 
  TIETONG      = 4,   // China TieTong (a.k.a RailCom)
  CERNET       = 8,   // China Education & Research
  GWBN         = 16,  // China Great-Wall Broadband
  CMCC         = 32,  // China Mobile
  BGP          = 64,  // BGP  
       
  MAX_ISP_TYPE = 64   // this MUST be the biggest available ISP value
};



int main(){
	int ISP[] = {0,1,2,4,8,16,32,64};
	//数组占用空间 
	int size= sizeof(ISP);  //32 ，总共8个元素，每个4个字节 
	int _size = sizeof(ISP[0]);//4估计是指针大小 
	int length = sizeof(ISP)/sizeof(ISP[0]) ; 
	std::cout <<"size :"<<size <<" ISP[0] size :"<<_size <<" length :"<<length<< std::endl;
	
	//编译不过？ 
	/*
	//vector的用迭代器做参数的构造函数 
	vector<int> vi(ISP, ISP+sizeof(ISP)/sizeof(ISP[0]));
	
	vector<int> vec;
	vec.swap(vi);
	vec.swap(vector<int>()); 
	*/
	
	ISPType isp = AUTO_DETECT; 
	//这样可以 ,数组赋值 
	vector<int> vec(ISP,ISP+8);
	vector<int>::iterator iter;
	for (iter = vec.begin();iter != vec.end(); ++iter ) {
		
		//测试或 |  
		isp = (ISPType)(isp | *iter );
		cout<< *iter <<" isp : "<<isp <<endl; 
	}
}


//好像编译不过啊 
/*
数组赋值给vector的快速方法

int a[]={1,2,4};
vector<int> vec(a,a+sizeof(a)/sizeof(a[0]));
vector<int> vec0;
vec0.swap(vec);
vec.swap(vector<int>());
*/ 



/*
主要是利用vector::reserve，vector::resize和memcpy或者assign这几个函数

stl容器中size()/resize(), reserve()/capacity()为两对对应接口，vector为保持高速随机访问，采用连续内存分配，如果插入一个新的元素，但是预留空间已经用完（size()==capacity()），此时会重新分配新的内存空间，将原空间的内容拷贝到新空间来，然后再插入新的元素。

示例：
//用reserve,resize,memcpy方法
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    int _i[]={1,2,3,4,5,6,7,8,9,10};  //可以是其他结构大小固定的结构体
    vector<int> _vec;
    _vec.reserve(10);   //预分配空间
    _vec.resize(10);     //指定元素数目，此处会有其他函数的调用，构造函数，拷贝等。（不够高效）
    memcpy(&_vec[0],_i,10*sizeof(int)); //内存拷贝
    for(vector<int>::iterator _it=_vec.begin();_it!=_vec.end();_it++) //测试结果
        cout<<*_it<<"   "; 
    cout<<endl;

    return 0;
}

编译运行，输出
1   2   3   4   5   6   7   8   9   10

//用reserve,assign方法
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int _i[]={1,2,3,4,5,6,7,8,9,10};  //可以是其他结构大小固定的结构体
    vector<int> _vec;
    _vec.reserve(10);   //预分配空间
    _vec.assign(&_i[0],&_i[10]);  //此方法应该比上一种速度要快些，因为直接拷贝赋值。
                                              //但是要注意数组的end地址为end[10]，而不是end[9]。
    for(vector<int>::iterator _it=_vec.begin();_it!=_vec.end();_it++) //测试结果
        cout<<*_it<<"   "; 
    cout<<endl;

    return 0;
}
编译运行，输出
1   2   3   4   5   6   7   8   9   10
个人分类： C++11

*/
