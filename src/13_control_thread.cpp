#include <iostream>
#include <string>
#include <thread>
 
void work(int& x) {
  std::cout << &x << std::endl;
  x = 12;
}

int main(int argc, char* argv[]) {
  int x = 10;
  std::thread t(work, std::ref(x));
  t.join();

  std::cout << &x << std::endl;
  std::cout << x << std::endl;
  return 0;
}