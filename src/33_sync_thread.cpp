#include <thread>
#include <future>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

void async_add(int a, int b, std::promise<int>& res){
    int c = a + b;
    res.set_value(c);
    std::this_thread::sleep_for(2s);
}

int main(int argc, char const *argv[])
{
    std::promise<int> promise;
    auto future = promise.get_future();
    auto res = std::async(std::launch::async, async_add, 3, 5, std::ref(promise)); 
    std::cout << future.get() << std::endl; // 能捕获到别的线程中的值
    return 0;
}
