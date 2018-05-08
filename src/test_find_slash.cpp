#include <iostream>
/* strstr example */
#include <stdio.h>
#include <string.h>

/*
http://www.cplusplus.com/reference/cstring/strstr/
*/

/*

#define STR(x) (((std::string)(x)).c_str())
这里强转会有一个个临时变量生成，用的实时，作用域会消失
*/
using namespace std;
#define STR(x) ((x).c_str())
int main(){
	char str[] = "http://c.biancheng.net";
    printf("%s\n", str);  //通过变量输出

	std::string surl ="rtsp://1.2.2.3/3";
	const char *url = STR(surl), *p = strstr(url, "://");
	printf("url %c \n",url[1]);
	if(p == NULL )
	{
		std::cout <<"not find ://"<<std::endl;
	}else{
		std::cout <<" find ://"<<std::endl;
	}
}
