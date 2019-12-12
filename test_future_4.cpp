#include <iostream>
#include <future>

void task() {
    for (int i = 0; i < 10; i++) {
        std::cout << "A";
    }
}

int main() {
    std::future<void> result{ std::async(task) };
    for (int i = 0; i < 10; i++) {
        std::cout << "B";
    }
    result.get();   //强制阻塞main线程，直到task线程执行完毕
    system("pause");
    return 0;
}

