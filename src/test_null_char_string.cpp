#include <stdio.h>
#include <iostream>
int main()
{
	char * msg=nullptr;
	std::string str = std::string(msg);
	printf("%s %s \n",msg,str.c_str());
	return 0;
}
