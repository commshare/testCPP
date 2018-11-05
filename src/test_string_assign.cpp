#include<iostream>
using namespace std;
//========================================
int main()
{
    string str1("hello");
    string str2;
    string str3;
    string str4;
    string str5;
    //====================================
    str2.assign(str1);
    str3.assign("World", 4);
    str4.assign(str1, 2, 3);
    str5.assign(10, 'c');
    //====================================
    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str3<<endl;
    cout<<str4<<endl;
    cout<<str5<<endl;
    //====================================
    system("pause");
    return 0;
}
