
#include<map>

#include <iostream>
#include <map>
#include <utility>

typedef std::pair<std::string,std::string> pair;


void add(std::map<pair,int> &map )
{
 std::string appName = "kkkkkk";

   std::string projectName = "yy-100edu-client-protosdk";
   const auto key = std::make_pair(projectName, appName);
   const auto sub = map.find(key);
     if (sub != map.end()) // found
     {
     		std::cout <<"found "<<std::endl;
     		
	 }else {
	 	std::cout <<"not found "<<std::endl;
	 		auto newSub = map.emplace(key, 1998);
	 }
	for (const auto &entry: map)
	{
		auto key_pair = entry.first;
		std::cout << "{" << key_pair.first << "," << key_pair.second << "}, "
				  << entry.second << '\n';
	}

}
int main()
{
	std::map<pair,int> map =
	{
		{ std::make_pair("C++", "C++14"), 2014 },
		{ std::make_pair("C++", "C++17"), 2017 },
		{ std::make_pair("Java", "Java 7"), 2011 },
		{ std::make_pair("Java", "Java 8"), 2014 },
		{ std::make_pair("C", "C11"), 2011 }
	};

  add(map);
  add(map);
    add(map);
	return 0;
}
