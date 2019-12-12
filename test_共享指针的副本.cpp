#include <functional>
#include <iostream>
//https://codeday.me/bug/20190729/1575750.html
struct C {
    C() {}
    C(const C& c) { ++s_copies; }

    void CallMe() const {}

    static int s_copies;
};

int C::s_copies = 0;

void Apply(const std::function<void()>& fct) { fct(); }

int main() {
    C c;
    std::function<void()> f0 = [c] { c.CallMe(); };
    // s_copies = 2
    std::cout <<" s_copies " <<C::s_copies <<std::endl;
    Apply(f0);
    // s_copies = 2
    std::cout <<" s_copies " <<C::s_copies <<std::endl;
}
