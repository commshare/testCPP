#include <iostream>
#include <thread>
#include <future>

using namespace std;


int main(int argc, char const *argv[]) {

    auto f =async([]{cout<<"hello"<<endl;});
    f.wait();

    return 0;
}
