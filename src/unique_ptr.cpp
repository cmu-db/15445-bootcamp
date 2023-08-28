/**
 * @file unique_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of a unique pointer.
 */

// A smart pointer is a type of data structure used for memory management (and
// sometimes other features) in languages that don't have memory management
// built in (e.g C++) An example of a language that has memory management built
// in is any language with garbage collection, like Java or Python. Two of the
// modern C++ standard library's smart pointers (and the ones that you will use
// in class) are std::unique_ptr and std::shared_ptr. Both std::unique_ptr and
// std::shared_ptr handle memory allocation and deallocation automatically, and
// contain raw pointers under the hood. In other words, they are wrapper classes
// over raw pointers. In this file, we'll talk about std::unique_ptr.
// std::unique_ptr is a type of smart pointer that retains sole ownership of an
// object This means that no two instances of std::unique_ptr can manage the
// same object.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes std::unique_ptr functionality.
#include <memory>
// String library for printing help for demo purposes.
#include <string>
// Including the utility header for std::move.
#include <utility>

// Basic point class. (Will use later)
class Point {
public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}
  inline int GetX() { return x_; }
  inline int GetY() { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }

private:
  int x_;
  int y_;
};

// Function that takes in a unique pointer reference and changes its x value to
// 445.
void SetXTo445(std::unique_ptr<Point> &ptr) { ptr->SetX(445); }

int main() {
  // This is how to initialize an empty unique pointer of type
  // std::unique_ptr<Point>.
  std::unique_ptr<Point> u1;
  // This is how to initialize a unique pointer with the default constructor.
  std::unique_ptr<Point> u2 = std::make_unique<Point>();
  // This is how to initialize a unique pointer with a custom constructor.
  std::unique_ptr<Point> u3 = std::make_unique<Point>(2, 3);

  // Here, for std::unique_ptr instance u, we use the statement (u ? "not empty"
  // : "empty") to determine if the pointer u contains managed data. The main
  // gist of this is that the std::unique_ptr class has a conversion function on
  // its objects to a boolean type, and so this function is called whenever we
  // treat the std::unique_ptr as a boolean. For instance, this can be used in
  // the following example.
  if (u1) {
    // This won't print because u1 is empty.
    std::cout << "u1's value of x is " << u1->GetX() << std::endl;
  }

  if (u2) {
    // This will print because u2 is not empty, and contains a managed Point
    // instance.
    std::cout << "u2's value of x is " << u2->GetX() << std::endl;
  }

  // Note that u1 is empty and u2 and u3 are not empty, since they were
  // initialized with a Point instance.
  std::cout << "Pointer u1 is " << (u1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u2 is " << (u2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;

  // Since instances of std::unique_ptr can have only one owner, it has no copy
  // constructor. Therefore, this code won't compile. Uncomment it to try!
  // std::unique_ptr<Point> u4 = u3;

  // However, it's possible to transfer ownership of unique pointers via
  // std::move.
  std::unique_ptr<Point> u4 = std::move(u3);

  // Note that because u3 is an lvalue, it no longer contains any managed
  // object. It is an empty unique pointer. Let's retest for emptyness.
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u4 is " << (u4 ? "not empty" : "empty") << std::endl;

  // Lastly, let's talk about how to pass std::unique_ptr instances as arguments
  // to functions. Mainly, you should pass it as a reference so that the
  // ownership doesn't change. You can see this as an example in the function
  // SetXTo445 (line 44 in this file).
  SetXTo445(u4);

  // Now, let's print the x value of u4 to confirm that the change occured, but
  // the ownership of the Point instance has been retained to u4.
  std::cout << "Pointer u4's x value is " << u4->GetX() << std::endl;

  return 0;
}