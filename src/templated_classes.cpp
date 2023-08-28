/**
 * @file templated_classes.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for templated classes.
 */

// Includes std::cout (printing).
#include <iostream>

// Templates can be also used to implement classes. For instance, here is a
// basic templated class that stores one element of a templated type and
// prints it when the print function is called.
template<typename T>
class Foo {
  public:
    Foo(T var) : var_(var) {}
    void print() {
      std::cout << var_ << std::endl;
    }
  private:
    T var_;
};

// You can also pass in multiple type names via templates into classes. 
// For instance, here's another basic templated class that stores two
// elements of a templated type and prints them when the print function
// is called.
template<typename T, typename U> 
class Foo2 {
  public:
    Foo2(T var1, U var2) 
      : var1_(var1)
      , var2_(var2) {}
    void print() {
      std::cout << var1_ << " and " << var2_ << std::endl;
    }
  private:
    T var1_;
    U var2_;
};

// It is also possible to create specialized templated classes, that do
// different things for different types. Take the following contrived example,
// which instantiates a class with a print function that outputs the value of
// the variable stored if it's any other type but float. If the class is 
// instantiated with a float type, it prints out hello float and the variable
// the class stores in its var_ field.
template<typename T>
class FooSpecial {
  public:
    FooSpecial(T var) : var_(var) {}
    void print() {
      std::cout << var_ << std::endl;
    }
  private:
    T var_;
};

// Specialized templated class, specialized on the float type.
template<>
class FooSpecial<float> {
  public:
    FooSpecial(float var) : var_(var) {}
    void print() {
      std::cout << "hello float! " << var_ << std::endl;
    }
  private:
    float var_;
};

// Template parameters don't have to be types. They can also be values!
template<int T>
class Bar {
  public: 
    Bar() {}
    void print_int() {
      std::cout << "print int: " << T << std::endl;
    }
};

int main() {
  // First, let us construct an object from a templated class. The Foo
  // class template is instantiated with an int template argument. This
  // would make a's type class Foo<int> instead of Foo. a's print 
  // function works as expected.
  Foo<int> a(3);
  std::cout << "Calling print on Foo<int> a(3): ";
  a.print();

  // It is also possible for a templated class to interpret the type
  // of its arguments. Once again, if you're a beginner, think twice
  // before doing this if you are unsure of the types you are 
  // instantiating your class with.
  Foo b(3.4f);
  std::cout << "Calling print on Foo b(3.4f): ";
  b.print();

  // Second, we construct an object from a templated class with multiple
  // type arguments.
  Foo2<int, float> c(3, 3.2f);
  std::cout << "Calling print on Foo2<int, float> c(3, 3.2f): ";
  c.print();

  // Let's see what happens when we instantiate FooSpecial both with
  // and without the float type argument. As expected when we call
  // print from d, it prints the variable and not "hello float".
  // When we call print from e, which is an instance of the
  // instantiated FooSpecial<float> class, it prints hello float!
  FooSpecial<int> d(5);
  std::cout << "Calling print on FooSpecial<int> d(5): ";
  d.print();

  FooSpecial<float> e(4.5);
  std::cout << "Calling print on FooSpecial<float> e(4.5): ";
  e.print();

  // Lastly, let's see what happens when we construct an object from a
  // templated class with non-type arguments.
  Bar<150> f;
  std::cout << "Calling print_int on Bar<150> f: ";
  f.print_int();

  // Once again, these are contrived examples, but it is still important
  // to understand them you'll be seeing code similar to this in the Bustub
  // codebase, so it's good to understand templated classes in these contexts!

  return 0;
}