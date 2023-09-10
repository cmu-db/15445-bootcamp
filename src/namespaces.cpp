/**
 * @file namespaces.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code on the usage of namespaces.
 */

// Namespaces provide scope to identifiers (the names of functions, types,
// variables). They are used to organize code into logical groups (e.g. a
// library might be one namespace). They also can prevent naming collisons
// between different identifiers. For instance, the C++ standard library
// uses the std namespace. This is why the print function in C++ is identified
// by std::cout, because the cout function is declared in the std
// namespace. C++ uses the :: operator for scope resolution, and therefore
// it is useful in differentiating which namespace a function, type,
// or class is declared in.

// In this file, we will introduce namespaces, namespace syntax, the using
// keyword, and calling functions from other namespaces.

// Includes std::cout (printing) for demo purposes.
#include <iostream>

// This is the syntax to declare a namespace.
namespace ABC {
  // We define a function spam in the ABC namespace. This is used in line 57.
  void spam(int a) {
    std::cout << "Hello from ABC::spam: " << a << std::endl;
  }

  // namespace DEF is a nested namespace, because it is declared inside namespace
  // ABC. The syntax for declaring a nested namespace is identical to the syntax of
  // declaring a non-nested namespace.
  namespace DEF {
    // We define a function bar inside the N::M namespace.
    void bar(float a) {
      std::cout << "Hello from ABC::DEF::bar: " << a << std::endl;
    }

    // We define a function uses_bar inside the ABC::DEF namespace. However, since
    // bar is in the same namespace as uses_bar (they're both in the ABC::DEF
    // namespace), the function bar is just referred to by its name in the
    // function uses_bar.
    void uses_bar(float a) {
      std::cout << "Hello from uses_bar: ";
      bar(a);
    }

    // We define a function uses_spam in the ABC::DEF namespace. To refer to 
    // ABC::spam from the ABC::DEF namespace, we have no other option but to
    // refer to it by its full identifier. Attempting to refer to it by spam
    // will result in a compilation error, stating that no function called spam
    // or ABC::DEF::spam exists. Note that it is possible to refer to every
    // function by its full identifier, but doing this makes coding speed 
    // inefficient.
    void uses_spam(int a) {
      std::cout << "Hello from uses_spam: ";
      ABC::spam(a);

      // Try uncommenting this code, which calls spam(a), here.
      // spam(a);
    }
  }

  // We define a function uses_DEF_bar inside the ABC namespace, but not inside the
  // DEF namespace. Since bar and uses_DEF_bar are both in the ABC namespace, the
  // function bar is referred to by DEF::bar (which is the differentiating
  // namespace) in the uses_DEF_bar function.
  void uses_DEF_bar(float a) {
    std::cout << "Hello from uses_DEF_bar: ";
    DEF::bar(a);
  }
}

// Both namespace A and namespace B have a function named foo with the same
// arguments and return value. This code will compile because overall, the
// two foo functions have different full identifiers, which are A::foo and
// B::foo.
namespace A {
  void foo(int a) {
    std::cout << "Hello from A::foo: " << a << std::endl;
  }
}

namespace B {
  void foo(int a) {
    std::cout << "Hello from B::foo: " << a << std::endl;
  }

  void peloton(int a) {
    std::cout << "Hello from B::peloton: " << a << std::endl;
  }
}

namespace C {
  void eggs(int a) {
    std::cout << "Hello from C::eggs: " << a << std::endl;
  }
}


// One of the uses of the using keyword is to bring the current namespace into
// the current scope. This statement will bring namespace B into the current
// scope. This means that B::foo can be referred to as foo in code anywhere
// below this line of code. In main, we will see that B::foo can be referred to
// by B::foo and by foo.
using namespace B;

// Another use of the using keyword is to bring certain members of a namespace
// into the current scope. This statement will bring C::eggs into the current
// scope. This means that eggs can be referred to as eggs anywhere below this
// line of code.
using C::eggs;

int main() {
  // The following line of code calls function spam (line 25). Calling spam(2)
  // will not work, as there is no function with the identifier spam, just
  // ABC::spam.
  ABC::spam(2);

  // The following line of code calls function bar. 
  ABC::DEF::bar(4.45);

  // The following line of code calls uses_bar. As expected, uses_bar will
  // print "Hello from uses_bar", and then call ABC::DEF::bar.
  ABC::DEF::uses_bar(6.45);

  // The following line of code calls uses_spam. As expected, uses_spam will
  // print "Hello from uses_spam", and then call ABC::spam.
  ABC::DEF::uses_spam(37);

  // The following line of code calls uses_DEF_bar. As expected, uses_DEF_bar
  // will print "Hello from uses_DEF_bar", and then call ABC::DEF::bar.
  ABC::uses_DEF_bar(3.12);

  // Now, let's talk the two foo functions. A::foo and B::foo are different 
  // functions with the same argument, and yet they are allowed to coexist,
  // since they have different identifiers. 
  A::foo(122);
  B::foo(150);

  // However, since line 106 brought the B namespace into the current scope,
  // it is possible to access anything from the B namespace without the B
  // namespace identifier. Therefore, it is possible to call B::foo by 
  // identifying it as foo.
  foo(440);

  // Likewise, since the entire namespace B was brought into the current
  // scope, it is also possible to refer to B::peloton, another function in
  // namespace B, as peloton.
  peloton(721);

  // Keep in mind that using the using keyword to bring an entire namespace
  // to the current scope can be risky, as you can risk naming conflicts 
  // if you are not careful. Therefore, we don't recommend you doing this.
  // However, it is possible to bring certain members of a namespace to
  // the current scope, such as the example on line 111. Here, we refer
  // to C::eggs by identifying it as eggs.
  eggs(999);

  return 0;
}
