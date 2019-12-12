//https://blog.csdn.net/stpeace/article/details/81274233 
//ԭ��hashmap���ǵͲ��ù�ϣ��ʵ�ֵ�map������ͨmap��key������� 
//cpp11�У�hashmap����unordered_map 
/*
 ?map��һ��ӳ�䣬 ��stl�У� map��ͨ���ײ�ĺ������ʵ�ֵģ� ���Ҹ��Ӷ���O(nlgn). ��Ȼ��Ҳ�����ù�ϣ����ʵ��map, Ҳ������Ҫ���ܵ�hashmap��

? ? ? ?rb tree--->stl map? ? ? ? ? ? ? ?�����Ҹ��Ӷ���O(nlogn)��key����

? ? ? ?hash table---> hash_map? ? ?(���Ҹ��Ӷ���O(1)�� key����)? ? ��C++11�У���Ӧ����unordered_map

?
��������������������������������
��Ȩ����������ΪCSDN������stpeace����ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/stpeace/article/details/81274233
*/
#include <iostream>
using namespace std;
 
// ��ϣ����
unsigned int hash_func(const string &key)
{
	unsigned int uiHash = 0;
	size_t nSize = key.size();
	for(size_t i = 0; i < nSize; i++)
	{
		std::cout <<" key[i] "<<key[i] <<std::endl;
		uiHash = uiHash << 7 ^ key[i];
	}
 
 //������64λ��ô 
	return (uiHash & 0x7FFFFFFF);
}
 
// ���
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
 
// ���ڹ�ϣ���map
class HashMap
{
private:
    Node **m_ppNode;               //  ����ָ�룬���ڹ���һ��ָ������
    unsigned int m_size;
 
public:
    HashMap(int size)
	{
		m_size = size;
		m_ppNode = new Node*[m_size];
		for (unsigned int i = 0; i < m_size; i++)
		{
			m_ppNode[i] = NULL;    // ��ʼ��һ��ָ������
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
		
		delete [] m_ppNode;      // []������
		m_ppNode = NULL;
	}
 
    void insert(const string& key, const string& value)
	{
	    int index = hash_func(key) % m_size;
	    std::cout <<" hash index is :"<<index <<std::endl;
	    Node *p = new Node(key, value);
		
		if(NULL == m_ppNode[index])
		{
			//�����ھ���index���� 
			m_ppNode[index] = p;
			return;
		}
 
		// ͷ�巨������, ����Ϊʲô
		Node *q = m_ppNode[index];
		//����ͷָ��ĺ��棬�൱��ͷ������ 
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
 
