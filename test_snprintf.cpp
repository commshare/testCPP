#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

int main(){
	std::string str = std::string( __FUNCTION__ ) + ":"+ std::to_string(__LINE__) ;

	
	std::cout <<str <<std::endl;
	
	return 0;
}
