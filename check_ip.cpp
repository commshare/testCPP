  // strTokenFunction.cpp : Check if the specified address is a valid numeric IP address.
  // This function is equavalent to the IPAddress.TryParse() method in C#

//#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
 

bool isIpOrDomain(char *st)
{
    int num, i, len;
    char *ch;

    //counting number of quads present in a given IP address
    int quadsCnt=0;

    printf("Split IP: \"%s\"\n", st);

    len = strlen(st);

    //  Check if the string is valid
    if(len<7 || len>15)
 //       return false;
	 {
	 	  printf(" IP: \"%s\" len  %d err\n", st,len);
 	}

    ch = strtok(st, ".");

    while (ch != NULL) 
    {
        quadsCnt++;
        printf("Quald %d is %s\n", quadsCnt, ch);

        num = 0;
        i = 0;

        //  Get the current token and convert to an integer value
        while(ch[i]!='\0')
        {
            num = num*10;
            num = num+(ch[i]-'0');
            i++;
        }

        if(num<0 || num>255)
        {
            printf("Not a valid ip\n");
           // return false;
        }

        if( (quadsCnt == 1 && num == 0) || (quadsCnt == 4 && num == 0))
        {
            printf("Not a valid ip, quad: %d AND/OR quad:%d is zero\n", quadsCnt, quadsCnt);
           // return false;
        }

        ch = strtok(NULL, ".");
    }

    //  Check the address string, should be n.n.n.n format
    if(quadsCnt!=4)
    {
        return false;
    }

    //  Looks like a valid IP address
    return true;
}
bool isValidIpAddress(char *st)
{
    int num, i, len;
    char *ch;

    //counting number of quads present in a given IP address
    int quadsCnt=0;

    printf("Split IP: \"%s\"\n", st);

    len = strlen(st);

    //  Check if the string is valid
    if(len<7 || len>15)
        return false;

    ch = strtok(st, ".");

    while (ch != NULL) 
    {
        quadsCnt++;
        printf("Quald %d is %s\n", quadsCnt, ch);

        num = 0;
        i = 0;

        //  Get the current token and convert to an integer value
        while(ch[i]!='\0')
        {
            num = num*10;
            num = num+(ch[i]-'0');
            i++;
        }

        if(num<0 || num>255)
        {
            printf("Not a valid ip\n");
            return false;
        }

        if( (quadsCnt == 1 && num == 0) || (quadsCnt == 4 && num == 0))
        {
            printf("Not a valid ip, quad: %d AND/OR quad:%d is zero\n", quadsCnt, quadsCnt);
            return false;
        }

        ch = strtok(NULL, ".");
    }

    //  Check the address string, should be n.n.n.n format
    if(quadsCnt!=4)
    {
        return false;
    }

    //  Looks like a valid IP address
    return true;
}

int main() 
{
	char st[] = "192.255.20.30"; //ok 
	bool ret = isIpOrDomain(st);
	
	
    //char st[] = "192.255.20.30"; //ok 
    //char st[] = "255.255.255.255"; //ok
    //char st[] = "0.255.255.0"; //not ok ip

    if(isValidIpAddress(st))
    {
        printf("The given IP is a valid IP address\n"); 
    }
    else
    {
        printf("The given IP is not a valid IP address\n");
    }
}
