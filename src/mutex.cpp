/**
 * @file mutex.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL mutex.
 */

// This program shows a small example of the usage of std::mutex. The
// std::mutex class provides the mutex synchronization primitive.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the mutex library header.
#include <mutex>
// Includes the thread library header.
#include <thread>

// Defining a global count variable and a mutex to be used by both threads.
int count = 0;

// This is the syntax for declaring and default initializing a mutex.
std::mutex m;

// The add_count function allows for a thread to increment the count variable
// by 1, atomically.
void add_count() {
  // Acquire the lock before accessing count, the shared resource.
  m.lock();
  count += 1;
  // Release the lock after accessing count, the shared resource.
  m.unlock();
}

// The main method constructs two thread objects and has them both run the
// add_count function in parallel. After these threads are finished executing,
// we print the count value, showing that both increments worked successfully.
// The std::thread library is the C++ STL library used to construct threads.
// You may view it as a C++ equivalent of the pthread library in C.
int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}