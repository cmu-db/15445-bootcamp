/**
 * @file move_constructors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for move constructors and move assignment operators.
 */

// Move constructors and move assignment operators are methods implemented
// inside of classes to effectively move resources from one object to the
// other, typically using std::move. These class methods take in another
// object of the same type, and move its resources to the instance
// where the method is called. In this file, we will explore implementing
// and using move constructors and move assignment operators.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the utility header for std::move.
#include <utility>
// Includes the C++ string library.
#include <string>
// Includes the header for uint32_t.
#include <cstdint>
// Includes the header for std::vector. We'll cover vectors more in
// containers.cpp, but what suffices to know for now is that vectors are
// essentially dynamic arrays, and the type std::vector<std::string> is an array
// of strings. Mainly, vectors take up a non-negligible amount of memory, and
// are here to show the performance benefits of using std::move.
#include <vector>

// Basic person class, with an implemented move constructor and move assignment
// operator, and a deleted copy constructor and copy assignment operator. This
// means that once an Person object is instantiated, it cannot be copied. It
// must be moved from one lvalue to another. Classes without copy operators are
// useful when it is imperative to only have one defined instance of a class.
// For instance, if a class manages a dynamically allocated memory block, then
// creating more than one instance of this class, without proper handling, can
// result in double deletion or memory leaks.
class Person {
public:
  Person() : age_(0), nicknames_({}), valid_(true) {}

  // Keep in mind that this constructor takes in a std::vector<std::string>
  // rvalue. This makes the constructor more efficient because it doesn't deep
  // copy the vector instance when constructing the person object.
  Person(uint32_t age, std::vector<std::string> &&nicknames)
      : age_(age), nicknames_(std::move(nicknames)), valid_(true) {}

  // Move constructor for class Person. It takes in a rvalue with type Person,
  // and moves the contents of the rvalue passed in as an argument to this
  // Person object instance. Note the usage of std::move. In order to ensure
  // that nicknames in object person is moved, and not deep copied, we use
  // std::move. std::move will cast the lvalue person.nicknames_ to an rvalue,
  // which represents the value itself. Also note that I don't call std::move
  // on the age_ field. Since it's an integer type, it's too small to incur a
  // significant copying cost. Generally, for numeric types, it's okay to copy
  // them, but for other types, such as strings and object types, one should
  // move the class instance unless copying is necessary.
  Person(Person &&person)
      : age_(person.age_), nicknames_(std::move(person.nicknames_)),
        valid_(true) {
    std::cout << "Calling the move constructor for class Person.\n";
    // The moved object's validity tag is set to false.
    person.valid_ = false;
  }

  // Move assignment operator for class Person.
  Person &operator=(Person &&other) {
    std::cout << "Calling the move assignment operator for class Person.\n";
    age_ = other.age_;
    nicknames_ = std::move(other.nicknames_);
    valid_ = true;

    // The moved object's validity tag is set to false.
    other.valid_ = false;
    return *this;
  }

  // We delete the copy constructor and the copy assignment operator,
  // so this class cannot be copy-constructed.
  Person(const Person &) = delete;
  Person &operator=(const Person &) = delete;

  uint32_t GetAge() { return age_; }

  // This ampersand at the return type implies that we return a reference
  // to the string at nicknames_[i]. This also implies that we don't copy
  // the resulting string, and the memory address this returns under the
  // hood is actually the one pointing to the nicknames_ vector's memory.
  std::string &GetNicknameAtI(size_t i) { return nicknames_[i]; }

  void PrintValid() {
    if (valid_) {
      std::cout << "Object is valid." << std::endl;
    } else {
      std::cout << "Object is invalid." << std::endl;
    }
  }

private:
  uint32_t age_;
  std::vector<std::string> nicknames_;
  // Keeping track of whether an object's data is valid, i.e. whether
  // all of its data has been moved to another instance.
  bool valid_;
};

int main() {
  // Let's see how move constructors and move assignment operators can be
  // implemented and used in a class. First, we create an instance of the class
  // Person. Note that the object andy is a valid object.
  Person andy(15445, {"andy", "pavlo"});
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // To move the contents of the andy object to another object, we can use
  // std::move in a couple ways. This method calls the move assignment operator.
  Person andy1;
  andy1 = std::move(andy);

  // Note that andy1 is valid, while andy is not a valid object.
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // This method calls the move constructor. After this operation, the contents
  // of the original andy object have moved to andy1, then moved to andy2. The
  // andy and andy1 lvalues are effectively defunct (and should not be used,
  // unless they are re-initialized).
  Person andy2(std::move(andy1));

  // Note that andy2 is valid, while andy1 is not a valid object.
  std::cout << "Printing andy2's validity: ";
  andy2.PrintValid();
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();

  // However, note that because the copy assignment operator is deleted, this code 
  // will not compile. The first line of this code constructs a new object via the
  // default constructor, and the second line invokes the copy assignment operator
  // to re-initialize andy3 with the deep-copied contents of andy2. Try uncommenting
  // these lines of code to see the resulting compiler errors.
  // Person andy3;
  // andy3 = andy2;

  // Because the copy constructor is deleted, this code will not compile. Try
  // uncommenting this code to see the resulting compiler errors.
  // Person andy4(andy2);

  return 0;
}
