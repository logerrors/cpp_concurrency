#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

static std::atomic<int> count = {1000000};

void hello(){
    while(count-- > 0){
        std::cout << "hello world" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(hello);
    std::thread t2(hello);

    t1.join();
    t2.join();
    return 0;
}