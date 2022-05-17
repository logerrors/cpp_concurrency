#include <atomic>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::atomic_long long_atomic;
    std::cout << long_atomic.is_lock_free() << std::endl;

    std::atomic_flag f = ATOMIC_FLAG_INIT;

    f.clear(std::memory_order_release);
    bool x = f.test_and_set();

    bool y = f.test_and_set();
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    return 0;
}
