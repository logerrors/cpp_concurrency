#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

struct Money{
    std::mutex a;
    std::mutex b;
    int da;
    int db;
};

void inc(Money& m){
    std::lock(m.a, m.b);
    std::lock_guard<std::mutex> g1(m.a, std::adopt_lock);
    std::this_thread::sleep_for(1s);
    std::lock_guard<std::mutex> g2(m.b, std::adopt_lock);
    m.da++;
    m.db++;
}

void dec(Money& m){
    std::lock(m.a, m.b);
    std::lock_guard<std::mutex> g1(m.b, std::adopt_lock);
    std::this_thread::sleep_for(1s);
    std::lock_guard<std::mutex> g2(m.a, std::adopt_lock);
    m.da--;
    m.db--;
}

int main(int argc, char const *argv[])
{

    Money m;
    m.da = 100;
    m.db = 1000;
    std::thread t1(inc, std::ref(m));
    std::thread t2(dec, std::ref(m));

    t1.join();
    t2.join();

    std::cout << m.da  << " " << m.db << std::endl;
    return 0;
}

