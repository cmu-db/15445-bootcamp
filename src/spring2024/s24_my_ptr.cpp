#include <iostream>
#include <memory>
#include <utility>

// This file contains the code used in the Spring2024 15-445/645 C++ bootcamp.
// It dives deeply into C++ new features like move constructor/assign operator, move semantics, unique_ptr,
// shared_ptr, wrapper class, etc., by implementing a simple version of unique_ptr from scratch.

// **IMPORTANT NOTES**:
//   1. please read `move_semantics.cpp` and `move_constructors.cpp` in `src` before reading this file!
//   2. please BEGIN your reading from the MAIN function!

// It is our implementation of std::unique_pointer<T>, and the real implementation is more complex!
// A template allows us to replace any type T, with what we want later in our code.
template <typename T>
class Pointer {
 public:
  Pointer() {
    ptr_ = new T;
    *ptr_ = 0;
    std::cout << "New object on the heap: " << *ptr_ << std::endl;
  }
  Pointer(T val) {
    ptr_ = new T;
    *ptr_ = val;
    std::cout << "New object on the heap: " << val << std::endl;
  }
  // Destructor is called whenever an instance gets out of scope (just when the stack pops).
  ~Pointer() {
    if (ptr_) {
      std::cout << "Freed: " << *ptr_ << std::endl;
      delete ptr_;
    }
  }

  // Copy constructor is explicitly deleted.
  Pointer(const Pointer<T> &) = delete;
  // Copy assignment operator is explicitly deleted.
  Pointer<T> &operator=(const Pointer<T> &) = delete;

  // Add move constructor: useful when we need to EXTEND the lifetime of an object!
  Pointer<T>(Pointer<T> &&another) : ptr_(another.ptr_) { another.ptr_ = nullptr; }
  // Add move assign operator: useful when we need to EXTEND the lifetime of an object!
  Pointer<T> &operator=(Pointer<T> &&another) {
    if (ptr_ == another.ptr_) {  // In case `p = std::move(p);`
      return *this;
    }
    if (ptr_) {  // We must free the existing pointer before overwriting it! Otherwise we LEAK!!
      delete ptr_;
    }
    ptr_ = another.ptr_;
    another.ptr_ = nullptr;  // NOTE: L14 avoids freeing nullptr during the destruction.
    return *this;
  }

  // Overload operator *, in order to make the Pointer<T> feel like a "pointer".
  // Note that the line below is an example of the following syntax we can use with our unique ptr type.
  // `p1.set_val(10)` -> `*p1 = 10`
  T &operator*() { return *ptr_; }

  T get_val() { return *ptr_; }
  void set_val(T val) { *ptr_ = val; }

 private:
  T *ptr_;
};

// INCORRECT version of smart_generator
template <typename T>
Pointer<int> &dumb_generator(T init) {
  Pointer<T> p(init);
  return p;  // NOOO! A DANGLING REFERENCE!
}

template <typename T>
Pointer<T> smart_generator(T init) {
  Pointer<T> p(init);
  return std::move(p);
  // Actually `return p` will also work, since C++ is smart, it knows move construtor should be invoked in this place.
  // You can refer to `Automatic l-values returned by value may be moved instead of copied` in
  // https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/ for more information.
}

void take_ownership(std::unique_ptr<int> p) {
  // Do something...
}

void not_take_ownership(int *p) {
  // Never `delete p` here!!
}

int main() {
  /* ======================================================================
     === Part 1: Common errors you come across in bustub ==================
     ====================================================================== */
  // When coding in C++/in this class, you will see a variable type called "unique_ptr"...
  std::unique_ptr<int> ptr = std::make_unique<int>(3);
  // What does this mean? Why we don't use the raw pointer like `int *p = new int`? (The answer is in Part 2)
  // And later, when you need to pass this unique_ptr to a function, you may write the following code (please
  // try to uncomment next line)...
  // take_ownership(ptr);
  // It doesn't work. The error is `Call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'`.
  // You may search the Internet, and other people tell you to add a thing called `std::move`...
  take_ownership(std::move(ptr));
  // It works! Looks great! And you continue coding...
  // Later, you may want to use p1 again (please try to uncomment next line)...
  // *ptr = 3;
  // Another error :(, and it says `segmentation fault`.
  // It looks confusing. What exactly happened?
  // We will explain it in this bootcamp, by implementing a simple version of unique_ptr from scratch!

  /* ======================================================================
     === Part 2: Why we need unique_ptr rather than the raw pointer =======
     ====================================================================== */
  // What's the problem of merely using the raw pointer?
  int *p = new int;  // Malloc
  *p = 456 * 12 / 34 + 23;
  if (*p == 76) {
    delete p;  // You may forget to add this line, and have `memory leak` problem!
    return 0;
  }
  delete p;  // Free

  // Raw pointers are dangerous! If you don't pay attention, you will come across problems like memory leaks, double
  // freeing, use after freeing...
  // The reason is that in C++, raw pointers have no inherent mechanism to clean up automatically!
  // Programmers have to allocate and deallocate heap memory all by themselves, and it is easy to go wrong.

  // We notice that, different from the memory in heap, the local variables in the stack will be created and deleted
  // automatically. Can we bind a raw pointer with a local variable in the stack?
  // It means, when this local variable is created, the heap memory for this raw pointer is automatically malloced.
  // And when this local variable dies, the raw pointer will be freed automatically. (For more details: search RAII)

  // Let's use C++ class to implement it!
  // Consider a class whose only job is to hold and "own" a raw pointer, and then deallocate that pointer when the class
  // object went out of scope...
  // This class is called `smart pointer`, and unique_ptr is one of smart pointers.
  // But, why we can't copy unique_ptr? What is std::move?

  /* ======================================================================
     === Part 3: Let's implement a unique_ptr class from scratch ==========
     ====================================================================== */
  // We only show the last version of our own unique_ptr class.
  // Here is the brief roadmap during the implementation:
  //  1. First version: with default copy constructor & assign operator, without move constructor & assign operator
  //     Problem: `Pointer p2 = p1` will cause `double free` problem
  //     Copy constructor & assign operator are evil in this case, since it will allow both p1 and p2 to manage the same
  //     raw pointer! Solution: disable copy constructor & assign operator
  //  2. Second version: without copy constructor & assign operator, without move constructor & assign operator
  //     `Pointer p2 = p1` won't compile, which is good. We can use reference `Pointer &p2 = p1` instead. But...
  //     Problem: we cannot implement functions like dumb_generator() or smart_generator()!
  //     Solution: add things called move constructor & assign operator
  //  3. Final version: without copy constructor & assign operator, with move constructor & assign operator
  //     `Pointer p4 = std::move(p3);`
  //     `std::move` guarantees this line of code invokes the `move constructor`(rather than `copy constructor`), to
  //     transfer the ownership of the raw pointer from p3 to p4!
  //     After this line, p3 will not be valid anymore!
  //     The ptr_ in p3 will be nullptr, please don't use p3 anymore unless you reassign it.
  // Now you understand what is `std::move`, why copy functions are deleted... And how to use unique_ptr!
  // Reference: Chapter 22 in Learncpp Website
  // (https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/)
  Pointer<int> p1(4);
  std::cout << "Hi from p1 " << p1.get_val() << std::endl;
  p1.set_val(10);
  std::cout << "Hi again from p1 " << p1.get_val() << std::endl;

  {
    // Problem in next line: both have the ownership of this raw pointer! Double free here!
    // Pointer<int> p2 = p1; // Code for 1st version implementation.
    // Solution: never allow to copy ownership of the pointer! Never copy!
    // After deleting copy assign operator & constructor, maybe we can use pointer to rewrite `p2 = p1`.
    Pointer<int> *p2 = &p1;  // Code for 2nd version implementation.
    std::cout << "Hi from p2 " << p2->get_val() << std::endl;
    // Wait this is dumb, we have a raw pointer again... Maybe we can use C++ reference, which is safer!
    // It's semantically the same thing with `Pointer<int> *p2 = &p1`, except the programmer doesn't **know** the pointer
    // (i.e. address of p2).
    Pointer<int> &p22 = p1;  // Code for 2nd version implementation.
    std::cout << "Hi from p22 " << p22.get_val() << std::endl;
  }
  // But reference doesn't solve everything :(
  // Sometimes we want to use the heap to extend the scope of the stack, like what dumb_generator() does!
  // Ex: pass down one element from a thread to another.
  // Please try to uncomment the following code!
  // Pointer<int>& dumb_pointer = dumb_generator(2); // Something will go horribly wrong, but what?
  // dumb_pointer.set_val(10); // Uh oh...

  // We need a way to "move the ownership". Please check move assign operator/constructor in Pointer class.
  // And we change dumb_generator() to smart_generator()...
  // Code for final version implementation:
  Pointer<int> p3 = smart_generator<int>(2);
  p3.set_val(10);
  Pointer<int> p4 = std::move(p3);

  // Let's make the user experience better.
  // 1. Templates.
  Pointer<float> p5(5.1);
  std::cout << "Hi from float p5 " << p5.get_val() << std::endl;
  // 2. Operator overload.
  Pointer<char> c1('a');
  *c1 = 'b';
  std::cout << "Hi from char c1 " << *c1 << std::endl;

  // You may be confused about:
  //  `Pointer<T> &&` (in the move constructor and assign operator)
  //                         VS
  //  `Pointer<T> &` (in the copy constructor and assign operator)

  // You have 2 options now. First, consider it as a syntax to distinguish copy and move, and go straight to Part 4;
  // Second, here is a quick explanation:
  // 1. You need to know lvalue & rvalue. According to Abi, a simplified definition of lvalues is that lvalues are
  // objects that refer to a location in memory. Rvalues are anything that is not a lvalue.
  // 2. `Pointer<T> &&` is a rvalue reference, while `Pointer<T> &` is a lvalue reference.
  // 3. `std::move(p)` will cast p from a lvalue to something, for example, a rvalue.
  // 4. For `Pointer p2 = p1`, it will invoke copy constructor, since p1 is a lvalue.
  // 5. For `Pointer p2 = std::move(p1)`, it will invoke move constructor, since std::move(p1) is a rvalue.

  /* ======================================================================
     === Part 4: Some important takeaways for unique_ptr & shared_ptr =====
     ====================================================================== */
  // Several important takeaways for unique_ptr: (Reference: https://www.learncpp.com/cpp-tutorial/stdunique_ptr/)
  // 1. Always use std::make_unique() to create a unique_ptr.
  std::unique_ptr<int> up{std::make_unique<int>(1)};
  // Please avoid writing the following code!
  // int *rp = new int;
  // std::unique_ptr<int> up1{ rp };
  // std::unique_ptr<int> up2{ rp }; // WRONG!

  // 2. Ways to pass std::unique_ptr to a function.
  not_take_ownership(up.get());
  // Unique_ptr `up` is still valid here!
  take_ownership(std::move(up));
  // Unique_ptr `up` cannot be used here!

  // Several important takeaways for shared_ptr: (Reference: https://www.learncpp.com/cpp-tutorial/stdshared_ptr/)
  // 0. Multiple shared ptrs can have the ownership of a raw pointer at the same time.
  //    Shared_ptr will count the number of shared ptrs that own the same raw pointer,
  //    and free the raw pointer **only if** count == 0.
  std::shared_ptr<int> sp1{std::make_shared<int>(1)};
  {
    // You can use copy constructor & assign operator for shared_ptr.
    std::shared_ptr<int> sp2 = sp1;
    std::cout << "Count: " << sp1.use_count() << std::endl;  // Output: 2
  }
  std::cout << "Count: " << sp1.use_count() << std::endl;  // Output: 1
  // 1. Always make a copy of an existing std::shared_ptr.
  int *rp = new int;
  std::shared_ptr<int> sp3{rp};
  // std::shared_ptr<int> sp4{ rp }; // WRONG!
  std::shared_ptr<int> sp4{sp3};
  // 2. Always use std::make_shared() to create a shared_ptr.

  return 0;
}
