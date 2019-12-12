#include <iostream>
#include <future>
#include <chrono>

bool is_prime(int x)
{
    for(int i=2;i<x;i++)
    {
        if(x%i==0)
            return false;

        return true;
    }
}

int main()
{
    std::future <bool> fut = std::async(is_prime,4444444444444444443);

    std::cout<<"wait,Checking";
    std::chrono::milliseconds span(10);
    while(fut.wait_for(span)==std::future_status::timeout)
        std::cout<<'.'<<std::flush;
        bool x = fut.get();
        std::cout<<"\n4444444444444444443"<<(x?" is":"is not") << " prime.\n";
        return 0;
}
