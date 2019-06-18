#include <stdio.h>
#include <iostream>

int main()
{
	
	int stride_y = 256;
	int stride_u = 128;
	int stride_v =128;
	int height = 180;
	int width = 240;
	int new_height = (height + 1) / 2; //90
	 int size = stride_y * height + (stride_u + stride_v) * ((height + 1) / 2); //69120
	 
	 int origin_size = width * height * 3/2; //64800
	 
	 printf("size %d new_height %d origin_size %d \n",size,new_height,origin_size);
	return 0;
}
