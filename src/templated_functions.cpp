/**
 * @file templated_functions.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for templated functions.
 */

// Includes std::cout (printing) for demo purposes.
#include <iostream>

// Templates are a language feature in C++ that allow you to write code that
// can work with multiple data types, without actually specifying those types.
// In C++, you can create both templated functions and templated classes. We'll
// talk about templated functions in this file.

// Here is a basic templated function that adds two numbers.
// Syntax note: You will see code with both template<class T> and
// template<typename T>. Although these statements are equivalent, there are
// differences between the class and typename keywords. This blog article covers
// this difference, but you won't need to know this for the class:
// https://mariusbancila.ro/blog/2021/03/15/typename-or-class/
template <typename T> T add(T a, T b) { return a + b; }

// It is possible to pass multiple type names via templates into functions.
// This function will print both of these values out.
template<typename T, typename U>
void print_two_values(T a, U b) {
  std::cout << a << " and " << b << std::endl;
}

// It is also possible to create specialized templated functions, that do
// different things for different types. Take the following contrived example,
// which prints the type if its a float type, but just prints hello world for
// all other types.
template <typename T> void print_msg() { std::cout << "Hello world!\n"; }

// Specialized templated function, specialized on the float type.
template <> void print_msg<float>() {
  std::cout << "print_msg called with float type!\n";
}

// Lastly, template parameters do not have to be classes. Take this basic (yet
// very contrived) function that takes in a bool as a template parameter and
// does different things to the argument depending on the boolean argument.
template <bool T> int add3(int a) {
  if (T) {
    return a + 3;
  }

  return a;
}

int main() {
  // First, let's see the add function called on both ints and floats.
  std::cout << "Printing add<int>(3, 5): " << add<int>(3, 5) << std::endl;
  std::cout << "Printing add<float>(2.8, 3.7): " << add<float>(2.8, 3.7)
            << std::endl;

  // It is also possible for a templated function to interpret the type of its
  // arguments, although if you're a beginner in modern C++, it's preferred you
  // don't do this because then you might not be sure of the types being passed
  // into your functions.
  std::cout << "Printing add(3, 5): " << add(3, 5) << std::endl;

  // Second, let's see the print_two_values function being called with two
  // different types.
  std::cout << "Printing print_two_values<int, float>(3, 3.2): ";
  print_two_values<int, float>(3, 3.2);

  // Let's see what happens when we called print_msg with and without the float
  // type being passed in. As expected, the first call to print_msg prints out
  // the general output, while the second one, with the float argument,
  // recognizes its type parameter and calls the specialized function.
  std::cout << "Calling print_msg<int>(): ";
  print_msg<int>();
  std::cout << "Calling print_msg<float>(): ";
  print_msg<float>();

  // add3 has the specified behavior for both a true and false templated
  // argument, as we can see here.
  std::cout << "Printing add3<true>(3): " << add3<true>(3) << std::endl;
  std::cout << "Printing add3<false>(3): " << add3<false>(3) << std::endl;

  // Lastly, it's important to note that most of these are contrived examples,
  // and it is possible to code some of these functions (e.g. passing a boolean
  // as an argument instead of a templated argument) without using templates.
  // However, in the class, you'll be seeing code similar to this in the
  // codebase, so it's good to understand templated functions in these contexts!

  return 0;
}