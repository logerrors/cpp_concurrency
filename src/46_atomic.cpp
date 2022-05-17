#include <atomic>
#include <thread>
#include <iostream>

std::atomic<long> count= 0;

void add(int c){
    for(auto i = 0 ; i < c; i++){
        count.fetch_add(1, std::memory_order_relaxed);
    }
}

int main(int argc, char const *argv[])
{
    int c = std::stoi(argv[1]);
    std::thread t1(add,c);
    std::thread t2(add,c);
    std::thread t3(add,c);
    std::thread t4(add,c);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << count << std::endl;
    return 0;
}
