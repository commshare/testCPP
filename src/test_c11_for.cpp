#include <stdio.h>
#include <set>
#include <stdlib.h>

int main()
{
	
	std::set<int> ss;
	ss.insert(100);
	ss.insert(65);
	
	for(const &it : ss)
	{
		int e = it;
		printf("%d \n",e);
	}
	
	return 0;
}


