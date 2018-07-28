#include<iostream>  
#include<set>  
#include<algorithm>  
#include<vector>  
using namespace std;  
void print(set<int> a)  
{  
    if(a.begin() == a.end())  
            cout << "}" << endl;  
    for(set<int>::iterator it = a.begin();it!=a.end();it++)  
    {  
        if(++it==a.end())  
        {  
            it--;  
            cout << *it << "}\n";  
        }  
        else  
        {  
            it--;  
            cout << *it << ", ";  
        }  
    }  
}  
int main()  
{  
    int T, cou = 0;  
    set<int> a, b, c;  
    cin >> T;  
    while(T--)  
    {  
        cou++;  
        a.clear(), b.clear(), c.clear();  
        int n;  
        cin >> n;  
        for(int i=0;i<n;i++)  
        {  
            int x;  
            cin >> x;  
            a.insert(x);  
        }  
        cin >> n;  
        for(int i=0;i<n;i++)  
        {  
            int x;  
            cin >> x;  
            b.insert(x);  
        }  
        cout << "Case# " << cou << ":" << endl;  
        cout << "A = {";  
        print(a);  
        cout << "B = {";  
        print(b);  
        set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));  
        cout << "A u B = {";  
        print(c);  
        c.clear();  
        set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));  
        cout << "A n B = {";  
        print(c);  
        c.clear();  
        set_difference(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));  
        cout << "A - B = {";  
        print(c);  
        c.clear();  
        set_difference(b.begin(),b.end(),a.begin(),a.end(),inserter(c,c.begin()));  
        cout << "SA = {";  
        print(c);  
        c.clear();  
        set_difference(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));  
        cout << "SB = {";  
        print(c);  
    }  
  
    return 0;  
}  
