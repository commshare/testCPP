#include <iostream>
#include <functional> //for std::hash
#include <string>

int main() {
    std::string str = "Hello World";
    std::hash<std::string> hasher;
    uint64_t hashed = hasher(str); //returns std::size_t
    std::cout << hashed << '\n'; //outputs 2146989006636459346 on my machine
    int i =0;
    std::string ip="187.6.23.121";
    uint64_t temp;
    for(i=0;i<100;i++)
    {
    
    	  auto hashed = hasher(ip);
    	  if(temp != hashed){
    	  	std::cout <<" hashed "<<hashed <<std::endl; 
		  }
		  temp = hashed;
	}
}
