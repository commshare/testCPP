#include <iostream>
#include <memory>

std::shared_ptr<int> get()
{
	
//return std::make_shared<int>();
return std::shared_ptr<int>(); //这个就是空 
}

int main(){

auto ptr = get();

if(ptr == nullptr)
{
	std::cout <<" ptr is null "<<std::endl; 
}else
{
		std::cout <<" ptr not null "<< *ptr <<std::endl; 
}
if(ptr.get()== nullptr)
{
		std::cout <<" ptrget is null "<<std::endl; 
}else
	std::cout <<" ptrget not null "<< * ptr.get() <<std::endl; 

return 0;
}

