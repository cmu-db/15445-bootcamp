/**
 * @file condition_variable.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL condition variable.
 */

// Includes std::cout (printing) for demo purposes.
#include <iostream>
#include <mutex>
#include <thread>

int count = 0;
std::mutex m;
std::condition_variable cv;

void add_count_and_notify() {
  std::scoped_lock slk(m);
  count += 1;
  cv.notify_one();
}

void waiter_thread() {
  std::unique_lock lk(m);
  cv.wait(lk, []{return count > 0;});

  std::cout << "Printing count: " << count << std::endl;
}

int main() {
  std::thread t1(add_count_and_notify);
  std::thread t2(waiter_thread);
  t1.join();
  t2.join();
  return 0;
}