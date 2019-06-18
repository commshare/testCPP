#include <iostream>
#include <map>
#include  <algorithm>
//https://www.cnblogs.com/motadou/archive/2009/02/01/1561549.html
/*

class map_finder即用于比较的函数对象，它的核心就是重载的()运算符。
因为每个容器迭代器的*运算符得到的结果都是该容器的value_type值，
所以该运算符的形参就是map迭代器指向的value_type类型的引用。
而map的value_type到底是什么类型，就得看下STL的源代码是如何定义的。

template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map
{
public:
typedef Key key_type;
typedef pair<const Key, T> value_type;
......
};
从上面的定义可以看出，map的value_type是std::pair<const Key, t>类型，它的first值就是关键字，second值保存map的值域。
*/ 
class map_finder

{
	public:
		map_finder(const std::string &cmp_string):m_s_cmp_string(cmp_string)
		{
		}
		//重载（） 
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
