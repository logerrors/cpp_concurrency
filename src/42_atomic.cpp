#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>


class spinlock_mutex{
public:
    spinlock_mutex():flag(ATOMIC_FLAG_INIT){};
    ~spinlock_mutex() = default;
    void lock(){
        while(flag.test_and_set(std::memory_order_acquire)){};
    }

    void unlock(){
        flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag;
};

spinlock_mutex spin_mu;
std::mutex mu;

long sum = 0;

void spin_add(){
    for(auto i = 0; i < 10000000; i++){
        std::lock_guard<spinlock_mutex> lg(spin_mu);
        sum++;
    }
}

void mu_add(){
    for(auto i = 0; i < 10000000; i++){
        std::lock_guard<std::mutex> lg(mu);
        sum++;
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(spin_add);
    std::thread t2(spin_add);
    std::thread t3(spin_add);
    std::thread t4(spin_add);
    std::thread t5(spin_add);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}