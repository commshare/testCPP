#include <iostream>
#include <set>

using namespace std;
//count() 用来查找set中某个某个键值出现的次数。这个函数在set并不是很实用，因为一个键值在set只可能出现0或1次，这样就变成了判断某一键值是否在set出现过了。
	
int count()
{
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    cout<<"set 中 1 出现的次数是 ："<<s.count(1)<<endl;
    cout<<"set 中 4 出现的次数是 ："<<s.count(4)<<endl;
    return 0;
}
//equal_range() ，返回一对定位器，分别表示第一个大于或等于给定关键值的元素和 第一个大于给定关键值的元素，这个返回值是一个pair类型，如果这一对定位器中哪个返回失败，就会等于end()的值。具体这个有什么用途我还没遇到过~~~

int equal_range()
{
    set<int> s;
    set<int>::iterator iter;
    for(int i = 1 ; i <= 5; ++i)
    {
        s.insert(i);
    }
    for(iter = s.begin() ; iter != s.end() ; ++iter)
    {
        cout<<*iter<<" ";
    }
    cout<<endl;
    //这是个what用法 
    pair<set<int>::const_iterator,set<int>::const_iterator> pr;
    pr = s.equal_range(3);
    cout<<"第一个大于等于 3 的数是 ："<<*pr.first<<endl;
    cout<<"第一个大于 3的数是 ： "<<*pr.second<<endl;
    return 0;
}
/*
erase(iterator)  ,删除定位器iterator指向的值

erase(first,second),删除定位器first和second之间的值

erase(key_value),删除键值key_value的值
*/ 

int erase()
{
    set<int> s;
    set<int>::const_iterator iter;
    set<int>::iterator first;
    set<int>::iterator second;
    for(int i = 1 ; i <= 10 ; ++i)
    {
        s.insert(i);
    }
    //第一种删除
    s.erase(s.begin());
    //第二种删除
    first = s.begin();
    second = s.begin();
    second++;
    second++;
    s.erase(first,second);
    //第三种删除
    s.erase(8);
    cout<<"删除后 set 中元素是 ：";
    for(iter = s.begin() ; iter != s.end() ; ++iter)
    {
        cout<<*iter<<" ";
    }
    cout<<endl;
    return 0;
}
//find()  ，返回给定值值得定位器，如果没找到则返回end()。
int find()
{
    int a[] = {1,2,3};
    set<int> s(a,a+3); //TODO !!!! 
	cout<<"a="<<*a<<endl;  //1
	cout<<"a+0 ="<<*(a+0) <<endl; //1 
	cout<<"a+1 ="<<*(a+1) <<endl; //2
	/*下面的俩值，竟然是一样的 TODO !!!*/
    cout<<"a+2 ="<<*(a+2) <<endl; //3
    cout<<"a+3 ="<<*(a+3) <<endl; //3
    set<int>::iterator iter;
    for(iter = s.begin();iter!= s.end();++iter){
    	cout<<*iter<<" ";
	}
    if((iter = s.find(2)) != s.end())
    {
        cout<<"find "<<*iter<<endl;
    }
    return 0;
}

/*
insert(key_value); 将key_value插入到set中 ，返回值是pair<set<int>::iterator,bool>，bool标志着插入是否成功，而iterator代表插入的位置，若key_value已经在set中，则iterator表示的key_value在set中的位置。

inset(first,second);将定位器first到second之间的元素插入到set中，返回值是void.
*/

int insert()
{
    int a[] = {1,2,3};
    set<int> s;
    set<int>::iterator iter;
    s.insert(a,a+3);
    for(iter = s.begin() ; iter != s.end() ; ++iter)
    {
        cout<<*iter<<" ";
    }
    cout<<endl;
    pair<set<int>::iterator,bool> pr; //返回值 
    pr = s.insert(5); //返回了 
    if(pr.second)  //值 
    {
        cout<<*pr.first<<endl;  //取迭代器 
    }
    return 0;
}
/*
lower_bound(key_value) ，返回第一个大于等于key_value的定位器

upper_bound(key_value)，返回最后一个大于等于key_value的定位器
*/

int bound()
{
    set<int> s;
    s.insert(1);
    s.insert(3);
    s.insert(4);
    cout<<*s.lower_bound(2)<<endl;
    cout<<*s.lower_bound(3)<<endl;
    cout<<*s.upper_bound(3)<<endl;
    return 0;
}
int main()
{
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    cout<<"set 的 size 值为 ："<<s.size()<<endl;
    cout<<"set 的 maxsize的值为 ："<<s.max_size()<<endl;
    cout<<"set 中的第一个元素是 ："<<*s.begin()<<endl;
    cout<<"set 中的最后一个元素是:"<<*s.end()<<endl;
    s.clear();
    if(s.empty())
    {
        cout<<"set 为空 ！！！"<<endl;
    }
    cout<<"set 的 size 值为 ："<<s.size()<<endl;
    cout<<"set 的 maxsize的值为 ："<<s.max_size()<<endl;
    
    count();
    equal_range();
    erase();
    find();
    insert();
    bound();
    return 0;
}
