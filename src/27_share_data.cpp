#include <mutex>
#include <iostream>

template<typename T>
class SING{
public:
    SING() = delete;
    SING(const SING&) = delete;
    SING(SING&& ) = delete;
    static T& instance(){
        static T t;
        return t;
    }
};

class Object{};

int main(int argc, char const *argv[])
{
    auto& o1 = SING<Object>::instance();
    auto& o2 = SING<Object>::instance();
    std::cout << &o1 << std::endl;
    std::cout << &o2 << std::endl;
    return 0;
}
