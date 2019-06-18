#include <stdio.h>
#include <stdlib.h>

int main()
{
	
int height = 240;
int width = 432;


int uv_height = (height + 1) / 2;
int uv_width = (width + 1) / 2;


        int uvHeight = height >> 1;
int uvWidth = width >> 1;

printf("h %d w %d , uvH %d uvW %d , uvH2 %d uvW2 %d \n ",height,width,uv_height,uv_width,uvHeight,uvWidth);

return 0;

}
