#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std::chrono_literals;

void do_some_work(){
   std::cout << "thread: " <<  std::this_thread::get_id() << std::endl;
   std::this_thread::sleep_for(2s);
}

int main()
{  
    std::vector<std::thread> threads;

    int max_size = 1000;
    while(max_size-- > 0){
        threads.emplace_back(do_some_work);
        std::this_thread::sleep_for(1ms);
        if(threads.size() % 100 == 0)std::cout << "thread num: " << threads.size() << std::endl;
    }

    std::for_each(threads.begin(), threads.end(), [](std::thread& t){
        if(t.joinable()){
            std::cout << "thread " << t.get_id() << " has joined" << std::endl;
            t.join();
        }
    });
    return 0;
}