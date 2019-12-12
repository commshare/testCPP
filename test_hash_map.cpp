//https://blog.csdn.net/stpeace/article/details/81274233 
//原来hashmap就是低层用哈希表实现的map啊，普通map的key是有序的 
//cpp11中，hashmap就是unordered_map 
/*
 ?map是一种映射， 在stl中， map是通过底层的红黑树来实现的， 查找复杂度是O(nlgn). 当然，也可以用哈希表来实现map, 也即本文要介绍的hashmap：

? ? ? ?rb tree--->stl map? ? ? ? ? ? ? ?（查找复杂度是O(nlogn)，key有序）

? ? ? ?hash table---> hash_map? ? ?(查找复杂度是O(1)， key无序)? ? 在C++11中，对应的是unordered_map

?
————————————————
版权声明：本文为CSDN博主「stpeace」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/stpeace/article/details/81274233
*/
#include <iostream>
using namespace std;
 
// 哈希函数
unsigned int hash_func(const string &key)
{
	unsigned int uiHash = 0;
	size_t nSize = key.size();
	for(size_t i = 0; i < nSize; i++)
	{
		std::cout <<" key[i] "<<key[i] <<std::endl;
		uiHash = uiHash << 7 ^ key[i];
	}
 
 //好像是64位的么 
	return (uiHash & 0x7FFFFFFF);
}
 
// 结点
class Node
{
public:
    string m_key;
    string m_value;
    Node *pNext;
 
public:
    Node(string key, string value)
    {
        m_key   = key;
        m_value = value;
        pNext   = NULL;
    }
};
 
// 基于哈希表的map
class HashMap
{
private:
    Node **m_ppNode;               //  二级指针，用于管理一级指针数组
    unsigned int m_size;
 
public:
    HashMap(int size)
	{
		m_size = size;
		m_ppNode = new Node*[m_size];
		for (unsigned int i = 0; i < m_size; i++)
		{
			m_ppNode[i] = NULL;    // 初始化一级指针数据
		}
	}
		
    ~HashMap()
	{
	    for (unsigned int i = 0; i < m_size; i++)
		{
			Node *p = m_ppNode[i];
			while (NULL != p)
			{
				Node *tmpP = p;
				p = p->pNext;
				
				delete tmpP;
				tmpP = NULL;
			}
		}
		
		delete [] m_ppNode;      // []不可少
		m_ppNode = NULL;
	}
 
    void insert(const string& key, const string& value)
	{
	    int index = hash_func(key) % m_size;
	    std::cout <<" hash index is :"<<index <<std::endl;
	    Node *p = new Node(key, value);
		
		if(NULL == m_ppNode[index])
		{
			//不存在就在index插入 
			m_ppNode[index] = p;
			return;
		}
 
		// 头插法，更好, 想想为什么
		Node *q = m_ppNode[index];
		//插在头指针的后面，相当于头部插入 
		m_ppNode[index]->pNext = p;
		// 
		p->pNext = q;
	}
 
    bool find(const string &key, string &value)
	{
	    unsigned int index = hash_func(key) % m_size;
	    if (NULL == m_ppNode[index])
    	{
    		value.clear();
			return false;
		}
	    
        Node *p = m_ppNode[index];
        while (NULL != p)
        {
            if (p->m_key == key)
            {
				value = p->m_value;
				return true;
			}
    
            p = p->pNext;
        }
 
		value.clear();
		return false;
	}
};
 
 
int main()
{
    HashMap hashmap(1000);
 
    hashmap.insert("a", "hello");
    hashmap.insert("bb", "linux");
    hashmap.insert("ccc", "good");
    hashmap.insert("dddd", "cpp");
 
	string strValue;
    cout << hashmap.find("bb", strValue) << endl;
	cout << strValue << endl;
 
    cout << hashmap.find("haha", strValue) << endl;
	cout << strValue << endl;
 
    cout << hashmap.find("ccc", strValue) << endl;
	cout << strValue << endl;
 
    return 0;
}
 
