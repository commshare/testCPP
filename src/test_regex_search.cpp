#include<iostream>
#include<regex>
#include<string>

int main()
{
	
	std::string s("this subject has a submarine as a subsequence");
	std::smatch m;
	std::regex e ("\\b(sub)([^ ]*)*"); //matches words beginning by "sub"
	
	std::cout<<"target sequence :" <<s << std::endl;
	std::cout <<"regular expression : /\\b(sub)([^ ]*/)" <<std::endl;
	std::cout << "the following matches " 
}
