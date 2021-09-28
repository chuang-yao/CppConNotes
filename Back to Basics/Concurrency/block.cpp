#include <iostream>
#include <thread>

int main() {
  int res = 0;

  std::thread threadB([&]() {
    std::cout << "Hello from threadB!\n";
    res = 42;
  });

  std::cout << "Hello from threadA!\n";
  std::cout << res << '\n';

  threadB.join();
  std::cout << res << '\n';
}
