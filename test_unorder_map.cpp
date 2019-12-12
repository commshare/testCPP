#include <iostream>
#include <unordered_map>

int main()
{
	std::unordered_map<std::string, int> mm;
	mm["zhang"] = 1;
	
	std::string host = "bin";
	auto itr = mm.find(host);
    if (itr != mm.end()) {
       std::cout <<" find "<< host <<std::endl;
    }else{
	  std::cout <<" not  find "<< host <<std::endl;
	}
	//直接erase回崩溃把
	//好像也没崩溃，啥都没做 
	mm.erase("tata"); 
	mm.erase("8888"); 
		
	std::cout <<"============"<<std::endl;
	for(auto &entry : mm)
	{
		std::cout <<" "<<entry.first << " " <<entry.second <<std::endl;
	}
	
	return 0;
}



