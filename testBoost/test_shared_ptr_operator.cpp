#include<boost/make_shared.hpp>
#include<boost/shared_ptr.hpp>
#include<vector>
#include<iostream>
/*
http://my.oschina.net/lingluonianhua/blog/212533
*/
using namespace std;
int main(){
    /*�����ڴ洢����shared_ptr*/
    typedef vector<boost::shared_ptr<int> > vs; //һ������shared_ptr�ı�׼��������   
	vs v(10); // //����һ��ӵ��10��Ԫ�ص�������Ԫ�ر���ʼ��Ϊ��ָ��       
	int i=0;
	for(vs::iterator pos =v.begin(); pos !=v.end(); ++pos){
		/*
		�Ե�����posʹ��һ�ν����ò�����*�Ի��shared_ptr,�����ӡ��������ָ�� 
		*(*pos)Ҳ����ֱ��д��**pos����ǰ�߸����������ߺ����������Ի�
		*/
		(*pos) = boost::make_shared<int>(++i); //ʹ�ù���������ֵ  
		cout<<"*pos["<<*pos<<"] and *(*pos)["<<*(*pos)<<"]"<<endl;
	}
	/*
	vector��operator[]�÷�����������ƣ�Ҳ��Ҫʹ��*��ȡ������ֵ��
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
�밴���������. . .
*/ 
