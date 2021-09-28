#include <iostream>
#include <mutex>
#include <thread>

int main() {
  std::mutex mtx;
  mtx.lock();
  std::thread threadB([&]() {
    mtx.lock();
    std::cout << "Hello from threadB!\n";
    mtx.unlock();
  });
  std::cout << "Hello from threadA!\n";
  mtx.unlock();
  threadB.join();
  std::cout << "Hello again from threadA!\n";
}
