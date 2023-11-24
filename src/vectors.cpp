/**
 * @file vectors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) vectors.
 */

// The C++ STL contains a container library, which is a generic collection of
// data structure and algorithm implementations that allow users to manipulate
// data structures like stacks, queues, and hash tables easily. Each container
// has its own header and usage. In the C++ standard (up to C++ 23), there are
// currently 20 containers, which is far too many to cover here well. In this
// file, we will introduce the container std::vector. The std::vector container
// is essentially a generic dynamic array (or unbounded array). We won't be
// able to cover every function in this container, but we will try to cover the
// basics of using this container.

// There is documentation on all the other functions, and other containers on
// https://en.cppreference.com/w/cpp/container. You will definitely need this
// resource as you complete the assignments in this class, so you should check
// it out!

// Includes std::remove_if to remove elements from vectors.
#include <algorithm>
// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the vector container library header.
#include <vector>

// Basic point class. (Will use later)
class Point {
public:
  Point() : x_(0), y_(0) {
    std::cout << "Default constructor for the Point class is called.\n";
  }

  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Custom constructor for the Point class is called.\n";
  }

  inline int GetX() const { return x_; }
  inline int GetY() const { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }
  void PrintPoint() const {
    std::cout << "Point value is (" << x_ << ", " << y_ << ")\n";
  }

private:
  int x_;
  int y_;
};

// A utility function to print the elements of an int vector. The code for this
// should be understandable and similar to the code iterating through elements
// of a vector in the main function.
void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

int main() {
  // We can declare a Point vector with the following syntax.
  std::vector<Point> point_vector;

  // It is also possible to initialize the vector via an initializer list.
  std::vector<int> int_vector = {0, 1, 2, 3, 4, 5, 6};

  // There are two functions for appending data to the back of the vector. They
  // are push_back and emplace_back. Generally, emplace_back is slightly faster,
  // since it forwards the constructor arguments to the object's constructor and
  // constructs the object in place, while push_back constructs the object, then
  // moves it to the memory in the vector. We can see this here where we add two
  // Point objects to our vector.
  std::cout << "Appending to the point_vector via push_back:\n";
  point_vector.push_back(Point(35, 36));
  std::cout << "Appending to the point_vector via emplace_back:\n";
  point_vector.emplace_back(37, 38);

  // Let's just add more items to the back of our point_vector.
  point_vector.emplace_back(39, 40);
  point_vector.emplace_back(41, 42);

  // There are many ways to iterate through a vector. For instance, we can
  // iterate through it's indices via the following for loop. Note that it is
  // good practice to use an unsigned int type for array or vector indexes.
  std::cout << "Printing the items in point_vector:\n";
  for (size_t i = 0; i < point_vector.size(); ++i) {
    point_vector[i].PrintPoint();
  }

  // We can also iterate through it via a for-each loop. Note that I use
  // references to iterate through it so that the items we iterate through are
  // the items in the original vector. If we iterate through references of the
  // vector elements, we can also modify the data in the vector.
  for (Point &item : point_vector) {
    item.SetY(445);
  }

  // Let's see if our changes went through. Note that I use the const reference
  // syntax to ensure that the data I'm accessing is read only.
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // Now, we show how to erase elements from a vector. First, we can erase
  // elements by their position via the erase function. For instance, if we want
  // to delete int_vector[2], we can call the following function with the
  // following arguments. The argument passed into this erase function has
  // the type std::vector<int>::iterator. An iterator for a C++ STL container
  // is an object that points to an element within the container. For instance,
  // int_vector.begin() is an iterator object that points to the first element
  // in the vector. The vector iterator also has a plus operator that takes
  // a vector iterator and an integer. The plus operator will increase the 
  // index of the element that the iterator is pointing to by the number passed
  // in. Therefore, int_vector.begin() + 2 is pointing to the third element in
  // the vector, or the element at int_vector[2].
  // If you are confused about iterators, it may be helpful to read the header of
  // iterator.cpp.
  int_vector.erase(int_vector.begin() + 2);
  std::cout << "Printing the elements of int_vector after erasing "
               "int_vector[2] (which is 2)\n";
  print_int_vector(int_vector);

  // We can also erase elements in a range via the erase function. If we want to
  // delete elements starting from index 1 to the end of the array, then we can
  // do so the following. Note that int_vector.end() is an iterator pointing to
  // the end of the vector. It does not point to the last valid index of the
  // vector. It points to the end of a vector and cannot be accessed for data.
  int_vector.erase(int_vector.begin() + 1, int_vector.end());
  std::cout << "Printing the elements of int_vector after erasing all elements "
               "from index 1 through the end\n";
  print_int_vector(int_vector);

  // We can also erase values via filtering, i.e. erasing values if they meet a
  // conditional. We can do so by importing another library, the algorithm
  // library, which gives us the std::remove_if function, which removes all
  // elements meeting a conditional from an iterator range. This does seem
  // awfully complicated, but the code can be summarized as follows.
  // std::remove_if takes in 3 arguments. Two of those arguments indicate the
  // range of elements that we should filter. These are given by
  // point_vector.begin() and point_vector.end(), which are iterators that point
  // to the beginning and the end of a vector respectively. Therefore, when we
  // pass these in, we are implying that we want the whole vector filtered.
  // The third argument is a conditional lambda type (see the std::function
  // library in C++, or at 
  // https://en.cppreference.com/w/cpp/utility/functional/function), that takes
  // in one argument, which is supposed to represent each element in the vector
  // that we are filtering. This function should return a boolean that is true
  // if the element is to be filtered out and false otherwise. std::remove_if
  // returns an iterator pointing to the first element in the container that
  // should be eliminated. Keep in mind that it swaps elements as needed,
  // partitioning the elements that need to be deleted after the iterator value
  // it returns. When erase is called, it deletes only the elements that
  // remove_if has partitioned away to be deleted, up to the end of the vector.
  // This outer erase takes a range argument, as we saw in the previous example.
  point_vector.erase(
      std::remove_if(point_vector.begin(), point_vector.end(),
                     [](const Point &point) { return point.GetX() == 37; }),
      point_vector.end());

  // After calling remove here, we should see that three elements remain in our
  // point vector. Only the one with value (37, 445) is deleted.
  std::cout << "Printing the point_vector after (37, 445) is erased:\n";
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // We discuss more stylistic and readable ways of iterating through C++ STL
  // containers in auto.cpp! Check it out if you are interested.

  return 0;
}
