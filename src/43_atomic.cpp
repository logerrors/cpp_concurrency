#include <atomic>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::atomic<bool> b;
    bool x = b.load(std::memory_order_acquire);
    std::cout << x << std::endl;
    b.store(true);
    x = b.exchange(false, std::memory_order_acq_rel);
    std::cout << x << std::endl;
    x = b.load(std::memory_order_acquire);
    std::cout << x << std::endl;

    bool expected = false;
    b.compare_exchange_weak(expected, true); // 当前值和期望值相同，就更新当前值为 true

    std::cout << b.load() << std::endl;
    std::cout << expected << std::endl;

    b.compare_exchange_weak(expected, true); // 当前值和期望值不同，更新期望值为当前值
    std::cout << b.load() << std::endl;
    std::cout << expected << std::endl;

    b.compare_exchange_strong(expected, false);
    return 0;
}
