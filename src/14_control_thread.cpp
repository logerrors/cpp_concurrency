#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
 
void work() {
    std::cout << "hello world" << std::endl;
    std::this_thread::sleep_for(3s);
}

int main(int argc, char* argv[]) {
    std::thread t1(work);
    std::cout << "t1 thread id" << t1.get_id() << std::endl;

    std::thread t2(std::move(t1));
    std::cout << "t2 thread id" << t2.get_id() << std::endl;

    if(t1.joinable()){
        std::cout << "t1 joined" << std::endl;
        t1.join();
    }

    if(t2.joinable()){
        std::cout << "t2 joined" << std::endl;
        t2.join();
    }
    return 0;
}