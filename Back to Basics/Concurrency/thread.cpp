#include <iostream>
#include <thread>

int main() {
  std::thread threadB([]() { std::cout << "Hello from threadB!\n"; });

  std::cout << "Hello from threadA!\n";

  threadB.join();
}
