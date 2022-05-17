#include <iostream>

static int count = 1000000;

int main(int argc, char const *argv[])
{
    for(int i = 0 ; i < count; i++)
        std::cout << "hello world" << std::endl;
    return 0;
}