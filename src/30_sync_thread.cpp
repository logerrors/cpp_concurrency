#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>

std::mutex g_mutex;
std::condition_variable g_cv;
std::list<int> g_list;
static const int COUNT = 100;
unsigned long long sum = 0;

void read_data(){
    while(true){
        std::unique_lock ul(g_mutex);
        g_cv.wait(ul, [](){
            return !g_list.empty();
        });
        auto data = g_list.front();
        g_list.pop_front();
        if(data == -1){
            break;
        }else{
            sum += data;
        }
    }
}

void write_data(){
    for(auto i = 1;i <= COUNT; i++){
        std::unique_lock ul(g_mutex);
        g_list.push_back(i);
        g_cv.notify_one();
    }
}


int main(int argc, char const *argv[])
{
    std::thread t1(write_data);
    std::thread t2(write_data);

    std::thread t3(read_data);


    t1.join();
    t2.join();
    
    // 标记结束
    {
        std::unique_lock ul(g_mutex);
        g_list.push_back(-1);
        g_cv.notify_one();
    }

    t3.join();

    std::cout << sum << std::endl;
    std::cout << g_list.size() << std::endl;
    return 0;
}
