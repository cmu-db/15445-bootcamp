/**
 * @file scoped_lock.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL scoped lock.
 */

// This program provides a small example of the use of std::scoped_lock.
// std::scoped_lock is a mutex wrapper class that provides a RAII-style
// method of obtaining and releasing locks. This means that when the object
// is constructed, the locks are acquired, and when the object is destructed,
// the locks are released.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the mutex library header.
#include <mutex>
// Includes the thread library header.
#include <thread>

// Defining a global count variable and two mutexes to be used by both threads.
int count = 0;
std::mutex m;

// The add_count function allows for a thread to increment the count variable
// by 1, atomically.
void add_count() {
  // The constructor of std::scoped_lock allows for the thread to acquire the
  // mutex m.
  std::scoped_lock slk(m);
  count += 1;

  // Once the function add_count finishes, the object slk is out of scope, and
  // in its destructor, the mutex m is released.
}

// The main method is identical to the one in mutex.cpp. It constructs the
// thread objects, runs add_count on both threads, and prints the result of
// count after execution.
int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}