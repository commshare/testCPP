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
	//����ռ�ÿռ� 
	int size= sizeof(ISP);  //32 ���ܹ�8��Ԫ�أ�ÿ��4���ֽ� 
	int _size = sizeof(ISP[0]);//4������ָ���С 
	int length = sizeof(ISP)/sizeof(ISP[0]) ; 
	std::cout <<"size :"<<size <<" ISP[0] size :"<<_size <<" length :"<<length<< std::endl;
	
	//���벻���� 
	/*
	//vector���õ������������Ĺ��캯�� 
	vector<int> vi(ISP, ISP+sizeof(ISP)/sizeof(ISP[0]));
	
	vector<int> vec;
	vec.swap(vi);
	vec.swap(vector<int>()); 
	*/
	
	ISPType isp = AUTO_DETECT; 
	//�������� ,���鸳ֵ 
	vector<int> vec(ISP,ISP+8);
	vector<int>::iterator iter;
	for (iter = vec.begin();iter != vec.end(); ++iter ) {
		
		//���Ի� |  
		isp = (ISPType)(isp | *iter );
		cout<< *iter <<" isp : "<<isp <<endl; 
	}
}


//������벻���� 
/*
���鸳ֵ��vector�Ŀ��ٷ���

int a[]={1,2,4};
vector<int> vec(a,a+sizeof(a)/sizeof(a[0]));
vector<int> vec0;
vec0.swap(vec);
vec.swap(vector<int>());
*/ 



/*
��Ҫ������vector::reserve��vector::resize��memcpy����assign�⼸������

stl������size()/resize(), reserve()/capacity()Ϊ���Զ�Ӧ�ӿڣ�vectorΪ���ָ���������ʣ����������ڴ���䣬�������һ���µ�Ԫ�أ�����Ԥ���ռ��Ѿ����꣨size()==capacity()������ʱ�����·����µ��ڴ�ռ䣬��ԭ�ռ�����ݿ������¿ռ�����Ȼ���ٲ����µ�Ԫ�ء�

ʾ����
//��reserve,resize,memcpy����
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    int _i[]={1,2,3,4,5,6,7,8,9,10};  //�����������ṹ��С�̶��Ľṹ��
    vector<int> _vec;
    _vec.reserve(10);   //Ԥ����ռ�
    _vec.resize(10);     //ָ��Ԫ����Ŀ���˴��������������ĵ��ã����캯���������ȡ���������Ч��
    memcpy(&_vec[0],_i,10*sizeof(int)); //�ڴ濽��
    for(vector<int>::iterator _it=_vec.begin();_it!=_vec.end();_it++) //���Խ��
        cout<<*_it<<"   "; 
    cout<<endl;

    return 0;
}

�������У����
1   2   3   4   5   6   7   8   9   10

//��reserve,assign����
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int _i[]={1,2,3,4,5,6,7,8,9,10};  //�����������ṹ��С�̶��Ľṹ��
    vector<int> _vec;
    _vec.reserve(10);   //Ԥ����ռ�
    _vec.assign(&_i[0],&_i[10]);  //�˷���Ӧ�ñ���һ���ٶ�Ҫ��Щ����Ϊֱ�ӿ�����ֵ��
                                              //����Ҫע�������end��ַΪend[10]��������end[9]��
    for(vector<int>::iterator _it=_vec.begin();_it!=_vec.end();_it++) //���Խ��
        cout<<*_it<<"   "; 
    cout<<endl;

    return 0;
}
�������У����
1   2   3   4   5   6   7   8   9   10
���˷��ࣺ C++11

*/
