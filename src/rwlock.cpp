/**
 * @file rwlock.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL std::shared_lock and std::unique_lock
 * (particularly usage of them as RWLocks).
 */

// Although C++ does not have a specific reader-writer's lock library, it is
// possible to emulate one by using the std::shared_mutex, std::shared_lock,
// and std::unique_lock libraries. This program shows a small example on how
// to do this.

// The std::shared_mutex is a mutex that allows for both shared, read-only
// locking, and exclusive, write-only locking. std::shared_lock can be used
// as an RAII-style read lock, and std::unique_lock can be used as a RAII-style
// write lock. scoped_lock.cpp talks about RAII-style locking in C++.

// If you would prefer to review the conceptuals of readers-writers locks and
// the reader-writers problem, you can refer to the 15-213/513/613 slides here:
// https://www.cs.cmu.edu/afs/cs/academic/class/15213-s23/www/lectures/25-sync-advanced.pdf

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the mutex library header.
#include <mutex>
// Includes the shared mutex library header.
#include <shared_mutex>
// Includes the thread library header.
#include <thread>

// Defining a global count variable and a shared mutex to be used by all threads.
// The std::shared_mutex is a mutex that allows for shared locking, as well as
// exclusive locking.
int count = 0;
std::shared_mutex m;

// This function uses a std::shared_lock (reader lock equivalent) to gain
// read only, shared access to the count variable, and reads the count
// variable.
void read_value() {
  std::shared_lock lk(m);
  std::cout << "Reading value " + std::to_string(count) + "\n" << std::flush;
}

// This function uses a std::unique_lock (write lock equivalent) to gain
// exclusive access to the count variable and write to the value.
void write_value() {
  std::unique_lock lk(m);
  count += 3;
}

// The main method constructs six thread objects and has two of them run the
// write_value function, and four of them run the read_value function, all
// in parallel. This means that the output is not deterministic, depending
// on which threads grab the lock first. Run the program a few times, and
// see if you can get different outputs.
int main() {
  std::thread t1(read_value);
  std::thread t2(write_value);
  std::thread t3(read_value);
  std::thread t4(read_value);
  std::thread t5(write_value);
  std::thread t6(read_value);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();

  return 0;
}