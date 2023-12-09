/**
 * @file shared_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of a shared pointer.
 */

// In this file, we'll talk about std::shared_ptr, which is a C++ smart pointer.
// See the intro of unique_ptr.cpp for an introduction on smart pointers.
// std::shared_ptr is a type of smart pointer that retains shared ownership of
// an object through a pointer. This means that multiple shared pointers can
// own the same object, and shared pointers can be copied.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes std::shared_ptr functionality.
#include <memory>
// Includes the utility header for std::move.
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

// Function that modifies a Point object inside a shared pointer
// by passing the shared pointer argument as a reference.
void modify_ptr_via_ref(std::shared_ptr<Point> &point) { point->SetX(15); }

// Function that modifies a Point object inside a shared pointer
// by passing the shared pointer argument as a rvalue reference.
void modify_ptr_via_rvalue_ref(std::shared_ptr<Point> &&point) {
  point->SetY(645);
}

void copy_shared_ptr_in_function(std::shared_ptr<Point> point) {
  std::cout << "Use count of shared pointer is " << point.use_count()
            << std::endl;
}

int main() {
  // This is how to initialize an empty shared pointer of type
  // std::shared_ptr<Point>.
  std::shared_ptr<Point> s1;
  // This is how to initialize a shared pointer with the default constructor.
  std::shared_ptr<Point> s2 = std::make_shared<Point>();
  // This is how to initialize a shared pointer with a custom constructor.
  std::shared_ptr<Point> s3 = std::make_shared<Point>(2, 3);

  // The specific syntax for checking whether a smart pointer is empty is
  // covered in unique_ptr.cpp (line 56). Note that s1 is empty, while s2 and
  // s3 are not empty.
  std::cout << "Pointer s1 is " << (s1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer s2 is " << (s2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer s3 is " << (s3 ? "not empty" : "empty") << std::endl;

  // It is possible to copy shared pointers via their copy assignment and copy
  // constructor operators. Using these copy operators will increase the
  // reference count of the overall object. Also, std::shared_ptr comes with
  // a method called use_count which keeps track of the number of objects
  // currently interacting with the same internal data as the current shared
  // pointer instance.

  // First, the number of references to pointer s3 is obtained. This should be
  // 1 because s3 is the only object instance using the data in s3.
  std::cout
      << "Number of shared pointer object instances using the data in s3: "
      << s3.use_count() << std::endl;

  // Then, s4 is copy-constructed from s3.
  // This is copy-construction because it is the first time s4 appears.
  std::shared_ptr<Point> s4 = s3;

  // Now, the number of references to pointer s3's data should be 2, since both
  // s4 and s3 have access to s3's data.
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after one copy: "
            << s3.use_count() << std::endl;

  // Then, s5 is copy-constructed from s4.
  std::shared_ptr<Point> s5(s4);

  // Now, the number of references to pointer s3's data should be 3, since s5,
  // s4, and s3 have access to s3's data.
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after two copies: "
            << s3.use_count() << std::endl;

  // Modifying s3's data should also change the data in s4 and s5, since they
  // refer to the same object instance.
  s3->SetX(445);

  std::cout << "Printing x in s3: " << s3->GetX() << std::endl;
  std::cout << "Printing x in s4: " << s4->GetX() << std::endl;
  std::cout << "Printing x in s5: " << s5->GetX() << std::endl;

  // It is also possible to transfer ownership of a std::shared_ptr by moving
  // it. Note that the pointer is empty after the move has occurred.
  std::shared_ptr<Point> s6 = std::move(s5);

  // Note that s5 is now empty, s6 refers to the same data as s3 and s4, and
  // there are still 3 shared pointer instances with access to the same Point
  // instance data, not 4.
  std::cout << "Pointer s5 is " << (s5 ? "not empty" : "empty") << std::endl;
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after two copies and a move: "
            << s3.use_count() << std::endl;

  // Similar to unique pointers, shared pointers can also be passed by reference
  // and rvalue reference. See unique_ptr.cpp (line 89) for a information on
  // passing unique pointers by reference. See references.cpp for more
  // information on references. See move_semantics.cpp for more information on
  // rvalue references. Here, we present code below that calls functions that
  // modify s2 by passing a shared pointer as a reference and as a rvalue
  // reference.
  modify_ptr_via_ref(s2);
  modify_ptr_via_rvalue_ref(std::move(s2));

  // After running this code, s2 should have x = 15 and y = 645.
  std::cout << "Pointer s2 has x=" << s2->GetX() << " and y=" << s2->GetY()
            << std::endl;

  // Unlike unique pointers, shared pointers can also be passed by value. In
  // this case, the function contains its own copy of a shared pointer, which
  // destroys itself after the function is finished. In this example, before s2
  // is passed to the function by value, its use count is 1. While it is in the
  // function, its use count is 2, because there is another copy of s2's data in
  // the shared pointer instance in the function. After the function goes out of
  // scope, this object in the function is destroyed, and the use count returns
  // to 1.
  std::cout
      << "Number of shared pointer object instances using the data in s2: "
      << s2.use_count() << std::endl;
  copy_shared_ptr_in_function(s2);
  std::cout << "Number of shared pointer object instances using the data in s2 "
               "after calling copy_shared_ptr_in_function: "
            << s2.use_count() << std::endl;

  return 0;
}
