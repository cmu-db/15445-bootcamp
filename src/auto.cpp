/**
 * @file auto.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of the auto keyword.
 */

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes string library.
#include <string>
// Including vector library.
#include <vector>
// Including unordered map library.
#include <unordered_map>

// The C++ auto keyword is a keyword that tells the compiler to infer the
// type of a declared variable via its initialization expression.
// It can be incredibly useful, as it allows for developer efficiency 
// (where the developer no longer has to type out long, unruly type
// names). It is also useful in the context of for-each loops.
// However, using auto poses a risk where the developer may not be aware
// of the types they are using, and therefore at risk for buggy and 
// non functional code. So be careful!

// Basic templated class with very long name, to show the usefulness of auto.
template<typename T, typename U>
class Abcdefghijklmnopqrstuvwxyz {
  public: 
    Abcdefghijklmnopqrstuvwxyz(T instance1, U instance2) 
    : instance1_(instance1)
    , instance2_(instance2) {}

    void print() const {
      std::cout << "(" << instance1_ << "," << instance2_ << ")\n";
    }
  private:
    T instance1_;
    U instance2_;
};

// Explicit template instantiation of the class
// Abcdefghijklmnopqrstuvwxyz<int, float>.
template class Abcdefghijklmnopqrstuvwxyz<int, float>;

// Templated function that returns an object of this class with a very long name.
template<typename T>
Abcdefghijklmnopqrstuvwxyz<T, T> construct_obj(T instance) {
  return Abcdefghijklmnopqrstuvwxyz<T, T>(instance, instance);
}

int main() {
  // The auto keyword is used to initialize the variable a. Here, the type
  // is inferred to be type int.
  auto a = 1;

  // Here are more examples of using auto to declare basic variables. 
  // Depending on the IDE being used, it might say what types a, b, and c
  // are.
  auto b = 3.2;
  auto c = std::string("Hello");

  // auto is not particularly useful for these prior examples. As one can
  // see, typing int a = 1;, float b = 3.2;, and std::string c = "Hello";
  // does not take significant overhead. However, there will definitely
  // be cases where the type name is long and complicated, or when the
  // type name is heavily templated, and using auto may be helpful.
  Abcdefghijklmnopqrstuvwxyz<int, int> obj = construct_obj<int>(2);
  auto obj1 = construct_obj<int>(2);

  // Maybe for one line it does not seem all that convenient, but imagine
  // if using this class with a very long name was useful in the code for
  // an extended period of time. Then, I'd imagine it would save a long
  // time!

  // The auto keyword is also useful for iterating through C++ containers.
  // For instance, let's construct a vector of type 
  // Abcdefghijklmnopqrstuvwxyz<int, float>, and discuss methods of iterating
  // through it.
  std::vector<Abcdefghijklmnopqrstuvwxyz<int, float>> vec;
  vec.emplace_back(2, 3.2);
  vec.emplace_back(4, 5.6);

  // One of the methods taught in vectors.cpp was to use a for-each loop to
  // iterate through the vector. Compare the readability of the two loops
  // below.
  std::cout << "Printing elements in vec...\n";
  for (const Abcdefghijklmnopqrstuvwxyz<int, float>& elem : vec) {
    elem.print();
  }
  std::cout << std::endl;

  std::cout << "Printing elements in vec with auto...\n";
  for (const auto& elem : vec) {
    elem.print();
  }
  std::cout << std::endl;

  // It is also possible to employ this technique to iterate through an
  // unordered map (and many other containers). Let's discuss how to do
  // this! First, we create an unordered map instance and add elements
  // to it.
  std::unordered_map<std::string, int> map;
  map.insert({{"andy", 445}, {"jignesh", 645}});
  
  // One method mentioned in unordered_map.cpp was to iterate through
  // a map by using a for loop with an iterator. Once again, compare
  // the readability of the two loops below.
  std::cout << "Printing elements in map...\n";
  for (std::unordered_map<std::string, int>::iterator it =  map.begin(); it != map.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")" << " ";
  }
  std::cout << std::endl;

  std::cout << "Printing elements in map with auto...\n";
  for (auto it =  map.begin(); it != map.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")" << " ";
  }
  std::cout << std::endl;
  
  // Overall, auto is a useful C++ keyword that can be used to write code more
  // efficiently, and to write cleaner and more readable code.
  // Keep in mind that using auto to iterate through C++ containers is better
  // in practice, since it produces more readable code. However, if you're not
  // sure of the types that are being used, it is always okay to revert back
  // to figuring out the type yourself.

  return 0;
}