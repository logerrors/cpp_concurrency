#include <thread>
#include <future>
#include <mutex>
#include <thread>
#include <iostream>

int async_add(int a, int b){
    return a + b;
}

int main(int argc, char const *argv[])
{
    std::packaged_task<decltype(async_add)> task(async_add);
    task(1,2);
    auto res = task.get_future();
    std::cout << res.get() << std::endl;
    // std::cout << res.get() << std::endl;// 只能 get 一次，后面会直接异常 future_error

    std::packaged_task<decltype(async_add)> task2(async_add);
    auto future = task2.get_future();
    std::thread t1(std::move(task2), 2, 3);

    t1.join();
    std::cout << future.get() << std::endl;
    return 0;
}
