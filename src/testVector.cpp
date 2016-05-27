/* 
 vector �ۺ���ϰ 
 Written by C_SuooL_Hu 
 2013 10 29  
*/   
  
#include <vector>  
#include <string>  
#include <iostream>  
#include <algorithm>  
  
using namespace std ;  
  
int main()  
{  
    // ���ֳ�ʼ����ʽ  
    vector<int> ivec_1; /*Ĭ�Ϲ��캯��v1λ��*/ 
    vector<int> ivec_2(ivec_1);  /*v2��v1��һ������*/
    vector<int> ivec_3(10, 0) ; /*v3����10��ֵΪ0��Ԫ��*/ 
    vector<int> ivec(10);  /*����ֵ��ʼ����Ԫ�ص�10������*/ 
    // �������������  
    vector<int>::iterator iter;  
    // �����±����  
    vector<int>::size_type ix ;   /*���ַ�ʽ�������±����*/
  
    system("echo off");  
    system("color 3") ;  
    // reset all the elements in ivec to 0  
    // ʹ���±����������Ϊ1  
    for (ix = 0; ix != ivec.size(); ++ix)  
            ivec[ix] = 1;          
    // print what we've got so far: should print 10 0's  
    cout << "ʹ���±긳ֵΪ1��vector<int>���ͣ�ͬ�����±���������:"<< endl;  
    for (ix = 0; ix != ivec.size(); ++ix)  
            cout << ivec[ix] << " ";  
    cout << endl;  
    // ʹ�õ������Ĳ�����ֵ������Ϊ0  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        *iter = 0;  
    // �������,ʹ�õ�����  
    cout<<"ʹ�õ�������ֵΪ0��vector<int>���ͣ�ͬ���õ��������������:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout<< endl ;  
  
    iter = ivec.begin();  
    while (iter != ivec.end())   
    {  
            *iter =2 ;  
            ++iter;  
    }  
    // �������,ʹ�õ�����  
    cout<<"ʹ��whileѭ���ĵ�������ֵΪ2�����е�vector<int>���ͣ�ͬ���õ��������������:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout<< endl << endl ;  
  
    // ʹ��vector�ĳ�Ա��������vector<int>��������  
    // ���Ԫ��  
    cout << "ʹ��vector�ĳ�Ա��������vector<int>��������" << endl;  
    cout << "���Ԫ��" << endl ;  
    cout << "ʹ�õ���������ӾŸ�����Ԫ��" << endl ;  
    for (ix = 0; ix != 10; ++ ix)  
        ivec.push_back(ix);  
    cout << "��ʱivec����" << ivec.size() << "��Ԫ��"<< endl;  
    // �������,ʹ�õ�����  
    cout<<"ʹ���±�����Ԫ��Ϊ�����ĵ����е�vector<int>���ͣ�ͬ���õ��������������:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout<< endl << endl;  
  
    // ����Ԫ��  
    cout << "����Ԫ�أ��ڵڶ���λ�ò���һ��43" << endl ;  
    ivec.insert(ivec.begin() + 1, 43);   // ��2λ�ò���һ��43����������������λ�á�  
    // �������,ʹ�õ�����  
    cout<<"ʹ�õ������������:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n��ʱivec����" << ivec.size() << "��Ԫ��"  ;  
    cout<< endl << endl ;  
  
    cout << "����Ԫ�أ��ڵ�һ��λ�ò�������13" << endl ;  
    ivec.insert(ivec.begin(), 3 , 13);  // ��1λ�ò���3��13���ݡ��޷���ֵ��  
    // �������,ʹ�õ�����  
    cout<<"ʹ�õ������������:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n��ʱivec����" << ivec.size() << "��Ԫ��";  
    cout<< endl << endl ;  
  
    cout << "����Ԫ�أ��ڵ�7��λ�ò���ivec��[1, 6) ֮������ݣ�" << endl ;  
    ivec.insert(ivec.begin()+6, ivec.begin(), ivec.begin()+5); // ��7λ�ò�����[10,19)��������ݡ��޷���  
    // �������,ʹ�õ�����  
    cout<<"ʹ�õ������������:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n��ʱivec����" << ivec.size() << "��Ԫ��";  
    cout<< endl << endl ;  
  
    cout << "ʹ��assign��ֵivec_1(��ivec�ĵ�[10��19����Ԫ�ظ�ֵ����):" <<endl ;  
    ivec_1.assign(ivec.begin()+9, ivec.begin()+18);  
    cout<<"ʹ�õ������������:" << endl;  
    for (iter = ivec_1.begin(); iter !=ivec_1.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n��ʱivec_1����" << ivec_1.size() << "��Ԫ��";  
    cout << endl;  
  
    cout << "ʹ��assign��ֵivec_2:" <<endl ;  
    ivec_2.assign(10,8) ;  
    cout<<"ʹ�õ������������:" << endl;  
    for (iter = ivec_2.begin(); iter !=ivec_2.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n��ʱivec_2����" << ivec_2.size() << "��Ԫ��";  
    cout << endl;  
    // Ԫ������  
    /* 
    ����vc 6.0��ģ���֧�ֲ����ã�������������޷�ͨ�����룬����ʹ��vs2010����ͨ���� 
    cout << "��ivec����" << endl; 
    bool Comp(const int &a,const int &b) 
    { 
        return a>b; 
    } 
    sort (ivec.begin(), ivec.end,Comp); 
    cout<<"�Ӵ�С�����ʹ�õ������������:" << endl; 
    for (iter = ivec_2.begin(); iter !=ivec_2.end(); ++iter ) 
        cout<< *iter << ' ' ; 
    */  
  
    cout << "�Ƿ�Ϊ�գ�0�����ǣ�1�����ǣ���" << ivec.empty() << endl;  
    ivec.clear() ;  
    cout << "���Ԫ��" << endl;  
    cout << "�Ƿ�Ϊ�գ�"  << ivec.empty() << endl;  
    return 0;  
}  
