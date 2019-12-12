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
    result.get();   //ǿ������main�̣߳�ֱ��task�߳�ִ�����
    system("pause");
    return 0;
}

