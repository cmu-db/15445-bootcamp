/**
 * @file unordered_maps.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) unordered_map.
 */

// In this file, we will introduce the container std::unordered_map. We won't
// be able to cover every function in this container, but we will try to cover
// the bare bones of using this container. Look to the intro of vectors.cpp for
// a general overview of C++ STL containers.

// There is documentation on all the other functions, and other containers
// on https://en.cppreference.com/w/cpp/container. You will definitely need this
// resource as you complete the assignments in this class, so you should check
// it out!

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the unordered_map container library header.
#include <unordered_map>
// Includes the C++ string library.
#include <string>
// Includes std::make_pair.
#include <utility>

int main() {
  // The std::unordered_map is a data structure that contains key-value pairs
  // with unique keys. Essentially, this means you can use it as a hash table
  // in your code.

  // You can declare a unordered_map with string keys and int values with
  // the following syntax.
  std::unordered_map<std::string, int> map;

  // The insert function is used to insert items into an unordered map.
  map.insert({"foo", 2});

  // The insert function also takes in a std::pair as the argument. An
  // std::pair is a generic pair type, and you can create one by calling
  // std::make_pair with 2 arguments. std::make_pair is defined in the header
  // <utility>, and constructs an instance of the generic pair type.
  map.insert(std::make_pair("jignesh", 445));

  // You can also insert multiple elements at a time by passing in an
  // initializer list of pairs.
  map.insert({{"spam", 1}, {"eggs", 2}, {"garlic rice", 3}});

  // It is also possible to insert an element via array-style syntax,
  // even if the element did not exist previously.
  map["bacon"] = 5;

  // You can also update an element in the unordered map with the same syntax.
  map["spam"] = 15;

  // The find function is used to find elements in an unordered map. It returns
  // an iterator pointing to the found element if the element exists, and
  // returns an iterator pointing to the end of the unordered map container
  // otherwise.
  std::unordered_map<std::string, int>::iterator result = map.find("jignesh");
  if (result != map.end()) {
    // This is one way of accessing the key/value pair from the iterator.
    std::cout << "Found key " << result->first << " with value "
              << result->second << std::endl;

    // Dereferencing the iterator is another method of accessing the key/value
    // pair from the iterator.
    std::pair<std::string, int> pair = *result;
    std::cout << "DEREF: Found key " << pair.first << " with value "
              << pair.second << std::endl;
  }

  // The count function returns the number of elements in an unordered map with
  // the specified key in the unordered map.
  size_t count = map.count("spam");
  if (count == 1) {
    std::cout
        << "A key-value pair with key spam exists in the unordered map.\n";
  }

  // The erase function deletes values from the unordered map. It can take a
  // key as an argument.
  map.erase("eggs");

  // We confirm that the eggs/2 key-value pair isn't in the map anymore.
  if (map.count("eggs") == 0) {
    std::cout << "Key-value pair with key eggs does not exist in the unordered "
                 "map.\n";
  }

  // Additionally, if we want to erase an element at a certain position, we can
  // pass in an iterator to the erase function. The following code will erase
  // the key-value pair with the key "garlic rice". Note that std::next is an
  // iterator function that returns the successor of the iterator passed in as
  // its argument.
  map.erase(map.find("garlic rice"));

  // We confirm that garlic rice/3 key-value pair isn't in the map anymore.
  if (map.count("garlic rice") == 0) {
    std::cout << "Key-value pair with key garlic rice does not exist in the "
                 "unordered map.\n";
  }

  // We can iterate through the unordered map elements via the unordered map
  // iterator. You cannot iterate through a unordered map via indexes of any
  // kind.
  std::cout << "Printing the elements of the iterator:\n";
  for (std::unordered_map<std::string, int>::iterator it = map.begin();
       it != map.end(); ++it) {
    // We can access the element itself by dereferencing the iterator.
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }
  std::cout << "\n";

  // Just like std::vector, we can also iterate through the unordered map
  // via a for-each loop.
  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const std::pair<const std::string, int> &elem : map) {
    std::cout << "(" << elem.first << ", " << elem.second << "), ";
  }
  std::cout << "\n";

  // We discuss more stylistic and readable ways of iterating through C++ STL
  // containers in auto.cpp! Check it out if you are interested.

  return 0;
}