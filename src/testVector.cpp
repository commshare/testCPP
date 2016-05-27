/* 
 vector 综合练习 
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
    // 四种初始化方式  
    vector<int> ivec_1; /*默认构造函数v1位空*/ 
    vector<int> ivec_2(ivec_1);  /*v2是v1的一个副本*/
    vector<int> ivec_3(10, 0) ; /*v3包含10个值为0的元素*/ 
    vector<int> ivec(10);  /*含有值初始化的元素的10个副本*/ 
    // 定义迭代器变量  
    vector<int>::iterator iter;  
    // 定义下标变量  
    vector<int>::size_type ix ;   /*这种方式来定义下标变量*/
  
    system("echo off");  
    system("color 3") ;  
    // reset all the elements in ivec to 0  
    // 使用下标操作，重置为1  
    for (ix = 0; ix != ivec.size(); ++ix)  
            ivec[ix] = 1;          
    // print what we've got so far: should print 10 0's  
    cout << "使用下标赋值为1的vector<int>类型（同样用下标遍历输出）:"<< endl;  
    for (ix = 0; ix != ivec.size(); ++ix)  
            cout << ivec[ix] << " ";  
    cout << endl;  
    // 使用迭代器的操作赋值，重置为0  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        *iter = 0;  
    // 遍历输出,使用迭代器  
    cout<<"使用迭代器赋值为0的vector<int>类型（同样用迭代器遍历输出）:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout<< endl ;  
  
    iter = ivec.begin();  
    while (iter != ivec.end())   
    {  
            *iter =2 ;  
            ++iter;  
    }  
    // 遍历输出,使用迭代器  
    cout<<"使用while循环的迭代器赋值为2的数列的vector<int>类型（同样用迭代器遍历输出）:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout<< endl << endl ;  
  
    // 使用vector的成员函数操作vector<int>类型数据  
    // 添加元素  
    cout << "使用vector的成员函数操作vector<int>类型数据" << endl;  
    cout << "添加元素" << endl ;  
    cout << "使用迭代器，添加九个递增元素" << endl ;  
    for (ix = 0; ix != 10; ++ ix)  
        ivec.push_back(ix);  
    cout << "此时ivec共有" << ivec.size() << "个元素"<< endl;  
    // 遍历输出,使用迭代器  
    cout<<"使用下标增加元素为递增的的数列的vector<int>类型（同样用迭代器遍历输出）:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout<< endl << endl;  
  
    // 插入元素  
    cout << "插入元素：在第二个位置插入一个43" << endl ;  
    ivec.insert(ivec.begin() + 1, 43);   // 在2位置插入一个43拷贝，传回新数据位置。  
    // 遍历输出,使用迭代器  
    cout<<"使用迭代器遍历输出:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n此时ivec共有" << ivec.size() << "个元素"  ;  
    cout<< endl << endl ;  
  
    cout << "插入元素：在第一个位置插入三个13" << endl ;  
    ivec.insert(ivec.begin(), 3 , 13);  // 在1位置插入3个13数据。无返回值。  
    // 遍历输出,使用迭代器  
    cout<<"使用迭代器遍历输出:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n此时ivec共有" << ivec.size() << "个元素";  
    cout<< endl << endl ;  
  
    cout << "插入元素：在第7个位置插入ivec的[1, 6) 之间的数据：" << endl ;  
    ivec.insert(ivec.begin()+6, ivec.begin(), ivec.begin()+5); // 在7位置插入在[10,19)区间的数据。无返回  
    // 遍历输出,使用迭代器  
    cout<<"使用迭代器遍历输出:" << endl;  
    for (iter = ivec.begin(); iter !=ivec.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n此时ivec共有" << ivec.size() << "个元素";  
    cout<< endl << endl ;  
  
    cout << "使用assign赋值ivec_1(将ivec的第[10，19）个元素赋值给他):" <<endl ;  
    ivec_1.assign(ivec.begin()+9, ivec.begin()+18);  
    cout<<"使用迭代器遍历输出:" << endl;  
    for (iter = ivec_1.begin(); iter !=ivec_1.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n此时ivec_1共有" << ivec_1.size() << "个元素";  
    cout << endl;  
  
    cout << "使用assign赋值ivec_2:" <<endl ;  
    ivec_2.assign(10,8) ;  
    cout<<"使用迭代器遍历输出:" << endl;  
    for (iter = ivec_2.begin(); iter !=ivec_2.end(); ++iter )  
        cout<< *iter << ' ' ;  
    cout << "\n此时ivec_2共有" << ivec_2.size() << "个元素";  
    cout << endl;  
    // 元素排序  
    /* 
    由于vc 6.0对模板库支持不够好，这里的排序函数无法通过编译，但是使用vs2010编译通过。 
    cout << "对ivec排序：" << endl; 
    bool Comp(const int &a,const int &b) 
    { 
        return a>b; 
    } 
    sort (ivec.begin(), ivec.end,Comp); 
    cout<<"从大到小排序后，使用迭代器遍历输出:" << endl; 
    for (iter = ivec_2.begin(); iter !=ivec_2.end(); ++iter ) 
        cout<< *iter << ' ' ; 
    */  
  
    cout << "是否为空（0代表不是，1代表是）：" << ivec.empty() << endl;  
    ivec.clear() ;  
    cout << "清空元素" << endl;  
    cout << "是否为空："  << ivec.empty() << endl;  
    return 0;  
}  
