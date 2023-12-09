/**
 * @file move_semantics.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for move semantics.
 */

// Move semantics in C++ are a useful concept that allows for the efficient
// and optimized transfer of ownership of data between objects. One of the
// main goals of move semantics is to increase performance, since moving an
// object is faster and more efficient than deep copying the object.

// To understand move semantics, one must understand the concept of lvalues
// and rvalues. A simplified definition of lvalues is that lvalues are objects
// that refer to a location in memory. Rvalues are anything that is not a
// lvalue.

// std::move is the most common way of moving an object from one lvalue to
// another. std::move casts an expression to a rvalue. This allows for us to
// interact with a lvalue as a rvalue, and allows for the ownership to be
// transferred from one lvalue to another.

// In the code below, we include some examples for identifying whether
// expressions in C++ are lvalues or rvalues, how to use std::move, and passing
// rvalues references into functions.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the utility header for std::move.
#include <utility>
// Includes the header for std::vector. We'll cover vectors more in
// containers.cpp, but what suffices to know for now is that vectors are
// essentially dynamic arrays, and the type std::vector<int> is an array of
// ints. Mainly, vectors take up a non-negligible amount of memory, and are here
// to show the performance benefits of using std::move.
#include <vector>

// Function that takes in a rvalue reference as an argument.
// It seizes ownership of the vector passed in, appends 3 to
// the back of it, and prints the values in the vector.
void move_add_three_and_print(std::vector<int> &&vec) {
  std::vector<int> vec1 = std::move(vec);
  vec1.push_back(3);
  for (const int &item : vec1) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

// Function that takes in a rvalue reference as an argument.
// It appends 3 to the back of the vector passed in as an argument,
// and prints the values in the vector. Notably, it does not seize
// ownership of the vector. Therefore, the argument passed in would
// still be usable in the callee context.
void add_three_and_print(std::vector<int> &&vec) {
  vec.push_back(3);
  for (const int &item : vec) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

int main() {
  // Take this expression. Note that 'a' is a lvalue, since it's a variable that
  // refers to a specific space in memory (where 'a' is stored). 10 is a rvalue.
  int a = 10;

  // Let's see a basic example of moving data from one lvalue to another.
  // We define a vector of integers here.
  std::vector<int> int_array = {1, 2, 3, 4};

  // Now, we move the values of this array to another lvalue.
  std::vector<int> stealing_ints = std::move(int_array);

  // Rvalue references are references that refer to the data itself, as opposed
  // to a lvalue. Calling std::move on a lvalue (such as stealing_ints) will
  // result in the expression being cast to a rvalue reference.
  std::vector<int> &&rvalue_stealing_ints = std::move(stealing_ints);

  // However, note that after this, it is still possible to access the data in
  // stealing_ints, since that is the lvalue that owns the data, not
  // rvalue_stealing_ints.
  std::cout << "Printing from stealing_ints: " << stealing_ints[1] << std::endl;

  // It is possible to pass in a rvalue reference into a function. However,
  // once the rvalue is moved from the lvalue in the caller context to a lvalue
  // in the callee context, it is effectively unusable to the caller.
  // Essentially, after move_add_three_and_print is called, we cannot use the
  // data in int_array2. It no longer belongs to the int_array2 lvalue.
  std::vector<int> int_array2 = {1, 2, 3, 4};
  std::cout << "Calling move_add_three_and_print...\n";
  move_add_three_and_print(std::move(int_array2));

  // It would be unwise to try to do anything with int_array2 here. Uncomment
  // the code to try it out! (On my machine, this segfaults...) NOTE: THIS MIGHT
  // WORK FOR YOU. THIS DOES NOT MEAN THAT THIS IS WISE TO DO! 
  // std::cout << int_array2[1] << std::endl;

  // If we don't move the lvalue in the caller context to any lvalue in the
  // callee context, then effectively the function treats the rvalue reference
  // passed in as a reference, and the lvalue in this context still owns the
  // vector data.
  std::vector<int> int_array3 = {1, 2, 3, 4};
  std::cout << "Calling add_three_and_print...\n";
  add_three_and_print(std::move(int_array3));

  // As seen here, we can print from this array.
  std::cout << "Printing from int_array3: " << int_array3[1] << std::endl;

  return 0;
}
