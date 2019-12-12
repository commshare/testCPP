#include <iostream>
#include <string>
#include <set>
#include <map>

int main()
{
	std::map<int,std::set<std::string>> m;
	auto v1 = m[1];
	v1.insert("zhang");
	
	for(auto &entry : m)
	{
		auto i = entry.first;
		std::cout <<"key "<< i <<std::endl;
		auto v = entry.second;
		for(auto &ee : v )
		{
			std::cout <<" ee" << ee <<std::endl;
		}
	}
	return 0;
}
