/**
 * @file iterator.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code on the usage and creation of iterators.
 */

// C++ iterators are objects that point to an element inside a container.
// They can be used to iterate through the objects of that container.
// One example of an iterator that you know is a pointer. A pointer
// can be used to iterate through a C style array. Take the following
// C-style code snippet:
// int *array = malloc(sizeof(int) * 10);
// int *iter = array;
// int zero_elem = *iter;
// iter++;
// int first_elem = *iter;
// As we can see, the ++ operator can be used to iterate through the
// C style array.
// There are a few examples about how to use iterators to access elements
// in C++ STL containers in vectors.cpp, sets.cpp, unordered_maps.cpp, 
// and auto.cpp. This is because using iterators in C++ to access and modify
// elements in C++ STL containers is considered good style, and worth
// mentioning in these files. This file will mainly focus on the implementation
// of iterators.

#include <cstdlib>

// This is an implementation of a doubly linked list. This class
// contains an iterator that iterates through the DLL.
struct Node {
  Node* next_;
  Node* prev_;
  int value_;
};

class DLL {
  public:
    DLL() 
    : head_(nullptr)
    , size_(0) {}

    Node* head_{nullptr};
    size_t size_;
};

int main() { return 0; }