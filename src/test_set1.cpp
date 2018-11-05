#include <iostream>
#include <set>

using namespace std;
//count() ��������set��ĳ��ĳ����ֵ���ֵĴ��������������set�����Ǻ�ʵ�ã���Ϊһ����ֵ��setֻ���ܳ���0��1�Σ������ͱ�����ж�ĳһ��ֵ�Ƿ���set���ֹ��ˡ�
	
int count()
{
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    cout<<"set �� 1 ���ֵĴ����� ��"<<s.count(1)<<endl;
    cout<<"set �� 4 ���ֵĴ����� ��"<<s.count(4)<<endl;
    return 0;
}
//equal_range() ������һ�Զ�λ�����ֱ��ʾ��һ�����ڻ���ڸ����ؼ�ֵ��Ԫ�غ� ��һ�����ڸ����ؼ�ֵ��Ԫ�أ��������ֵ��һ��pair���ͣ������һ�Զ�λ�����ĸ�����ʧ�ܣ��ͻ����end()��ֵ�����������ʲô��;�һ�û������~~~

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
    //���Ǹ�what�÷� 
    pair<set<int>::const_iterator,set<int>::const_iterator> pr;
    pr = s.equal_range(3);
    cout<<"��һ�����ڵ��� 3 ������ ��"<<*pr.first<<endl;
    cout<<"��һ������ 3������ �� "<<*pr.second<<endl;
    return 0;
}
/*
erase(iterator)  ,ɾ����λ��iteratorָ���ֵ

erase(first,second),ɾ����λ��first��second֮���ֵ

erase(key_value),ɾ����ֵkey_value��ֵ
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
    //��һ��ɾ��
    s.erase(s.begin());
    //�ڶ���ɾ��
    first = s.begin();
    second = s.begin();
    second++;
    second++;
    s.erase(first,second);
    //������ɾ��
    s.erase(8);
    cout<<"ɾ���� set ��Ԫ���� ��";
    for(iter = s.begin() ; iter != s.end() ; ++iter)
    {
        cout<<*iter<<" ";
    }
    cout<<endl;
    return 0;
}
//find()  �����ظ���ֵֵ�ö�λ�������û�ҵ��򷵻�end()��
int find()
{
    int a[] = {1,2,3};
    set<int> s(a,a+3); //TODO !!!! 
	cout<<"a="<<*a<<endl;  //1
	cout<<"a+0 ="<<*(a+0) <<endl; //1 
	cout<<"a+1 ="<<*(a+1) <<endl; //2
	/*�������ֵ����Ȼ��һ���� TODO !!!*/
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
insert(key_value); ��key_value���뵽set�� ������ֵ��pair<set<int>::iterator,bool>��bool��־�Ų����Ƿ�ɹ�����iterator��������λ�ã���key_value�Ѿ���set�У���iterator��ʾ��key_value��set�е�λ�á�

inset(first,second);����λ��first��second֮���Ԫ�ز��뵽set�У�����ֵ��void.
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
    pair<set<int>::iterator,bool> pr; //����ֵ 
    pr = s.insert(5); //������ 
    if(pr.second)  //ֵ 
    {
        cout<<*pr.first<<endl;  //ȡ������ 
    }
    return 0;
}
/*
lower_bound(key_value) �����ص�һ�����ڵ���key_value�Ķ�λ��

upper_bound(key_value)���������һ�����ڵ���key_value�Ķ�λ��
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
    cout<<"set �� size ֵΪ ��"<<s.size()<<endl;
    cout<<"set �� maxsize��ֵΪ ��"<<s.max_size()<<endl;
    cout<<"set �еĵ�һ��Ԫ���� ��"<<*s.begin()<<endl;
    cout<<"set �е����һ��Ԫ����:"<<*s.end()<<endl;
    s.clear();
    if(s.empty())
    {
        cout<<"set Ϊ�� ������"<<endl;
    }
    cout<<"set �� size ֵΪ ��"<<s.size()<<endl;
    cout<<"set �� maxsize��ֵΪ ��"<<s.max_size()<<endl;
    
    count();
    equal_range();
    erase();
    find();
    insert();
    bound();
    return 0;
}
