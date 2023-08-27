/**
 * @file mutex.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL mutex.
 */

// Includes std::cout (printing) for demo purposes.
#include <iostream>
#include <mutex>
#include <thread>

int count = 0;
std::mutex m;

void add_count() {
  m.lock();
  count += 1;
  m.unlock();
}

int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}