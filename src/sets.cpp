/**
 * @file sets.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) sets.
 */

// In this file, we will introduce the container std::set. We won't be able
// to cover every function in this container, but we will try to cover the
// basics of using this container. Look to the intro of vectors.cpp for
// a general overview of C++ STL containers.

// The std::set container is a data structure that contains a sorted set of
// unique objects of a single type. It is usually implemented as a Red-Black
// tree, if that helps you conceptualize the std::set. The std::set container
// is used to maintain of a set of unique elements.

// There is documentation on all the other functions, and other containers
// on https://en.cppreference.com/w/cpp/container. You will definitely need this
// resource as you complete the assignments in this class, so you should check
// it out!

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the set container library header.
#include <set>

int main() {
  // We can declare a int set with the following syntax.
  std::set<int> int_set;

  // To insert elements, we use the insert function. Here we insert elements 1
  // through 10 in our set. There also exists an emplace function that allows
  // the user to construct objects in place for set insertion. We cover emplace
  // more in vectors.cpp (line 73).
  for (int i = 1; i <= 5; ++i) {
    int_set.insert(i);
  }

  for (int i = 6; i <= 10; ++i) {
    int_set.emplace(i);
  }

  // To find an element, we can use the find function, which returns an
  // iterator that points to the element within the set with the key that is
  // equivalent to the key argument. We can then check to see whether this
  // returned iterator is equivalent to the end iterator. If the returned
  // iterator value is equivalent to the end iterator value, then this would
  // imply that the element does not exist.
  std::set<int>::iterator search = int_set.find(2);
  if (search != int_set.end()) {
    std::cout << "Element 2 is in int_set.\n";
  }

  // We can also use the count function, which returns the number of elements
  // with the specified key in the set.
  if (int_set.count(11) == 0) {
    std::cout << "Element 11 is not in the set.\n";
  }

  if (int_set.count(3) == 1) {
    std::cout << "Element 3 is in the set.\n";
  }

  // To erase an element, we can use the erase function. The erase function can
  // firstly, take a key to erase. For instance, if we want to erase 4 from the
  // set, we can call:
  int_set.erase(4);

  // We confirm that 4 isn't in the set anymore.
  if (int_set.count(4) == 0) {
    std::cout << "Element 4 is not in the set.\n";
  }

  // Additionally, if we want to erase an element at a certain position, we can
  // pass in an iterator to the erase function. Let's say we want to erase the
  // first element from the set. We can pass in an iterator that points to the
  // first element from the set to the erase function.
  int_set.erase(int_set.begin());

  // We confirm that 1 isn't in the set anymore.
  if (int_set.count(1) == 0) {
    std::cout << "Element 1 is not in the set.\n";
  }

  // Lastly, we can erase elements in the set by passing in an iterator range to
  // the erase function. For instance, if we want to erase elements that are
  // greater than or equal to 9 (so, 9 and 10), we call the following.
  int_set.erase(int_set.find(9), int_set.end());

  // We confirm that 9 and 10 aren't in the set anymore.
  if (int_set.count(9) == 0 && int_set.count(10) == 0) {
    std::cout << "Elements 9 and 10 are not in the set.\n";
  }

  // We can iterate through the set elements via the set iterator. You cannot
  // iterate through a set via indexes of any kind.
  std::cout << "Printing the elements of the iterator:\n";
  for (std::set<int>::iterator it = int_set.begin(); it != int_set.end();
       ++it) {
    // We can access the element itself by dereferencing the iterator.
    std::cout << *it << " ";
  }
  std::cout << "\n";

  // Just like std::vector, we can also iterate through the set via a for-each
  // loop.
  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const int &elem : int_set) {
    std::cout << elem << " ";
  }
  std::cout << "\n";

  // We discuss more stylistic and readable ways of iterating through C++ STL
  // containers in auto.cpp! Check it out if you are interested.

  return 0;
}