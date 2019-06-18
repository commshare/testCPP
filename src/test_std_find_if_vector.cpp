/*
template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map
{
public:
typedef Key key_type;
typedef pair<const Key, T> value_type;
......
};
从上面的定义可以看出，map的value_type是std::pair<const Key, t>类型，它的first值就是关键字，second值保存map的值域。

3 -- find_if在std::vector的应用
vector的find_if用法与map的很相似，区别仅仅是二者的value_type不一样而已。我们看下vecotr对value_type的定义。

template <class T, class Alloc = alloc>
class vector
{
public:
typedef T value_type;
typedef value_type* iterator;
......
};
*/

#include <vector>
#include <string>
#include  <algorithm>
struct value_t
{int a ;
int b;
};

class vector_finder
{
	public:
	vector_finder(const int a )	:m_i_a (a) {
	} 
	
	bool operator () ( const std::vector<struct value_t > :: value_type  &value)
	{
		return value.a == m_i_a;
	}
	private:
		int m_i_a;
};


int main()
{
	std::vector <struct value_t > my_vector;
	struct value_t my_value;
	my_value.a = 11;
	my_value.b =  1000;
	my_vector.push_back(my_value);
	 my_value.a = 12; my_value.b = 1000;
	 my_vector.push_back(my_value);
	 
   std::vector<struct value_t > ::iterator itr = my_vector.end();
   itr = std::find_if(my_vector.begin(),my_vector.end(),vector_finder(11));
   if(itr == my_vector.end())
   {
   	printf("not find \n");
   }
   else{	
   
     printf("found value.a:%d value.b:%d\n", itr->a, itr->b);
   }
     return 0;     
}
