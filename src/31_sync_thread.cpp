#include <future>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

int find_the_answer(){
    std::cout << "inside thread " <<  std::this_thread::get_id() << std::endl;
    return 0;
}

void do_other_stuff(){
    std::cout << "sleep for 1s" << std::endl;
    std::this_thread::sleep_for(1s);
}

int main(int argc, char const *argv[])
{
    std::cout << "main thread " << std::this_thread::get_id() << std::endl;
    std::future<int> the_answer = std::async(find_the_answer);
    do_other_stuff();
    std::cout << "this answer is " << the_answer.get() << std::endl;
    return 0;
}
