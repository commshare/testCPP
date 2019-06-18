#include <iostream>
#include <map>
#include  <algorithm>
//https://www.cnblogs.com/motadou/archive/2009/02/01/1561549.html
/*

class map_finder�����ڱȽϵĺ����������ĺ��ľ������ص�()�������
��Ϊÿ��������������*������õ��Ľ�����Ǹ�������value_typeֵ��
���Ը���������βξ���map������ָ���value_type���͵����á�
��map��value_type������ʲô���ͣ��͵ÿ���STL��Դ��������ζ���ġ�

template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map
{
public:
typedef Key key_type;
typedef pair<const Key, T> value_type;
......
};
������Ķ�����Կ�����map��value_type��std::pair<const Key, t>���ͣ�����firstֵ���ǹؼ��֣�secondֵ����map��ֵ��
*/ 
class map_finder

{
	public:
		map_finder(const std::string &cmp_string):m_s_cmp_string(cmp_string)
		{
		}
		//���أ��� 
		bool operator() (const std::map <int , std::string >::value_type &pair )
		{
			return pair.second == m_s_cmp_string;
		}
	private:
		const std::string &m_s_cmp_string;	
			
 } ;
 
 int main()
 {
 	std::map <int ,std::string> my_map;
	 my_map.insert(std::make_pair(10,"china"));
	 my_map.insert(std::make_pair(20,"usa")); 
	 my_map.insert(std::make_pair(30, "english"));
	 my_map.insert(std::make_pair(40,"hongk"));
	 
	 std::map<int , std::string>::iterator it  = my_map.end();
	 
	 #if 0 
	 it = std::find_if(my_map.begin(),my_map.end(),map_finder("china")) ;
	 #else
	 std::string cmpstr = "china";
	 //lamda
	  it = std::find_if(my_map.begin(),my_map.end(),
	  [=](decltype(my_map)::value_type &pair)
	  {
		return pair.second == cmpstr;
	  }
	  ) ;
	 #endif
	 if(it == my_map.end())
	 {
	 	printf("not find \n");
	 }else
	 {
	 	printf(" found key %d value %s \n",it->first,it->second.c_str());
	 }
	 return 0;
 }
