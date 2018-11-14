//https://www.cnblogs.com/yyxt/p/4253088.html 
//¥˙¬Î∂º±‡“Î±®¥Ì∞° 
#pragma GCC diagnostic error "-std=c++11"  
#include<functional>

std::function< size_t (const char*) > print_func;  

//normal function --> std::function object 

size_t CPrint(const char*) { ... }  

print_func = CPrint ;

print_func("hello"); 

//function -->std::funciton objet

class CxxPrint
{
	public:
		size_t operator() (const char *) { ... }
};

CxxPrint p;
print_func = p;
print_func("world");


