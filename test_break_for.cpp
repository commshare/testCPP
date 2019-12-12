#include<iostream>
using namespace std;

int main()
{
    int i = 0;
    for( ;i<100; )
    {
        cout << i << endl;
        if( i>10 )
        {
            break; //break»áÌø³öforºÍwhile 
        }

        i = i+1;
    }
    return 0;
}
