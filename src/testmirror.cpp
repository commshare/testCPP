#include<stdio.h>
#include<stdlib.h>

void mirror(int *y,int *o)
{
	y=o;
}

int main()
{
	int o = 100;
	int * y = NULL;
	mirror(y,&o);
	if(y != NULL)
	{
		printf(" y %d \n",*y);
	}else
	{
		printf(" y is null \n");
	}
	return 0;
}
