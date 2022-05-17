#include <thread>
#include <algorithm>
#include <iostream>

template<typename T>
class Print
{
public:
    void operator() (T elem) const{
        std::cout << elem << std::endl;
    }
};

void print(int elem){
    std::cout << elem << std::endl;
}

class Printer {
public:
    Printer() = default;
    ~Printer() = default;
    void print(){
        std::cout << this->elem << std::endl;
    }
private:
    int elem = {3};
};


int main(int argc, char const *argv[])
{
    // 重载函数调用运算符
    Print<int> p;
    std::thread t1(p,3);
    t1.join();

    // lambda 表达式
    std::thread t2([](int elem){
        std::cout << elem << std::endl;
    }, 3);
    t2.join();

    // 函数指针
    std::thread t3(print, 3);
    t3.join();


    // 普通函数对象
    std::thread t4(std::bind(print, std::placeholders::_1), 3);
    t4.join();

    // 包装了成员函数的函数对象
    Printer printer;
    std::thread t5(std::mem_fn(&Printer::print), &printer);
    t5.join();
    return 0;
}
