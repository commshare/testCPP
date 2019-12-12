#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;
 
bool isSpace(char x) { return x == ' '; }
 
int main()
{
	string s2("Text with    spaces");
	cout << "删除之前"<<s2 << endl;
	s2.erase(remove_if(s2.begin(), s2.end(), isSpace), s2.end());
	cout <<"删除之后"<< s2 << endl;
	
	
	vector<string> str = { "apple", "banana", "key", "cat", "dog", "orange", "banana" };
	auto find_str = "banana";
	auto sd = remove_if(str.begin(), str.end(), [find_str](string n) { return n == find_str; });
	str.erase(sd, str.end());
 
	str.erase(remove_if(str.begin(), str.end(),
		[find_str](string n) { return n == find_str; }),
		str.end());
	vector<string>::iterator iter;
	for (iter = str.begin(); iter != str.end(); ++iter)
	{
		cout << "删除之后："<<*iter<<" "<< endl;
	}

   std::set<int > msgdiset ={1,2,3,4,5};
   int id = 3;
   	  bool ret=false;
	  for (auto it = msgdiset.begin(); it != msgdiset.end();)
	  {
		if ( *it == id)
		{
		  it = msgdiset.erase(it);
		  ret = true;
		}
		else
		{
		  it++;
		}
	  }
	  for(auto & entry: msgdiset)
	  {
	  	//这里直接就是引用了，不需要加* 就可以。 
	  	std::cout <<entry<<endl;
	  }
	return 0;
}

