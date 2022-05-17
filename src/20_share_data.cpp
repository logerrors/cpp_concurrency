#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include <thread>

struct empty_stack: std::exception
{
    const char* what() const throw()
    {
        return "empty stack";
    }

};

template<typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data=other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        value=data.top();
        data.pop();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

void play_stack1(threadsafe_stack<int> & stack){
    for(auto i = 0; i < 20000000; i++){
        stack.push(i);
        int j;
        stack.pop(j);
    }
}

void play_stack2(threadsafe_stack<int> & stack){
    for(auto i = 0; i < 20000000; i++){
        stack.push(i);
        stack.push(i*2);
        auto m = stack.pop();
        auto n = stack.pop();
    }
}

int main()
{
    threadsafe_stack<int> si;
    std::thread t1(play_stack1, std::ref(si));

    std::thread t2(play_stack2, std::ref(si));

    t1.join();
    t2.join();
    return 0;
}