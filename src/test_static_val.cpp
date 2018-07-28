#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
 #include <stdint.h>


void check(int i){
	int val = 100;
	val = val + i;
	static int now = val;
	printf("now %d ",now);
	printf("val %d ",val);
	now = val;
	printf("now %d \n",now);
}

int main()
{
	//static局部变量只被初始化一次，下一次依据上一次结果值； 　
	for(int i =200;i<1000;i+=100)
	{
		check(i);
	}
	return 0;
}
/*
now 300 val 300
now 300 val 400
now 300 val 500
now 300 val 600
now 300 val 700
now 300 val 800
now 300 val 900
now 300 val 1000

--------------------------------
Process exited after 0.09977 seconds with return value 0
请按任意键继续. . .
*/
