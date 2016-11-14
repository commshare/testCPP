#include<stdio.h>
#include<stdlib.h>

int main(){
	int choice =2;
	int flag=1;
	int set=0;
	
	while(flag){
	switch(choice){
		case 1:
			printf("#####1#########\n");
			flag=0;
			set=3; 
			break;
		case 2:
			printf("####2#####");
			set=1;
			choice=1; 
			continue; /*重新执行while,不进入set语句，此时choice为1，执行switch case1, set为3，*/
		default:
			printf("===default===\n");
	}
	if(set==1){
		printf("choice 2 make set  1");
	}
	if(set == 3) 
		printf("choice 1 make set  3");
	}

	return 0;
}
