# 15-445/645 C++ Bootcamp
This bootcamp aims to provide a basic introduction to coding in modern C++. 
The features of the C++ language are too vast and expansive to cover in one
bootcamp, and quite frankly, it is learned best through experience. The staff
is certain that 15-445 will make you a more confident C++ programmer! 
However, we do cover some C++ topics that are necessary to know while doing
the programming assignments. This tutorial does not cover basic C/C++ syntax.
It mainly covers C++ programming features, particularly concepts that do not exist in C.

Feedback for the C++ bootcamp is always appreciated! Feel free to submit issues/PRs.

## Format
The bootcamp consists of C++ code files, located in `src/`, that are meant
to be read in depth. Each of these files can be compiled into an executable
with the same name. Use CMake to build these executables. This set of commands
should build all the executables. After running these commands, these executables
should be located in the `build` directory.
```console
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```
For instance, the `src/references.cpp` file compiles into the `references`
executable, located in `./build`. The same holds for every file in the source
directory.

## Files
There are fifteen files in the `src/` directory, each which cover different
concepts. They are meant to be read in the order below, since each file 
builds up on the previous one. However, if you know some modern C++ concepts
and are looking to refresh your knowledge, it is probably okay to start by
reading the files on concepts you are unfamiliar about.

### References and Move Semantics
- `references.cpp`: Covers C++ references.
- `move_semantics.cpp`: Covers C++ move semantics.
- `move_constructors.cpp`: Covers C++ class move constructors and move assignment operators.

### C++ Templates
- `templated_functions.cpp`: Covers C++ templated functions.
- `templated_classes.cpp` Covers C++ templated classes.

### Misc
- `wrapper_class.cpp`: Covers C++ wrapper classes.
- `iterator.cpp`: Covers implementing a basic C++ style iterator.
- `namespaces.cpp`: Covers C++ namespaces.

### C++ Standard Library (STL) Containers
- `vectors.cpp`: Covers `std::vector`.
- `set.cpp`: Covers `std::set`.
- `unordered_map.cpp`: Covers `std::unordered_map`.
- `auto.cpp`: Covers the usage of the C++ keyword `auto`, including using `auto` to iterate through C++ STL containers.

### C++ Standard Library (STL) Memory
- `unique_ptr.cpp`: Covers `std::unique_ptr`.
- `shared_ptr.cpp`: Covers `std::shared_ptr`.

### C++ Standard Library (STL) Synch Primitives
- `mutex.cpp`: Covers `std::mutex`.
- `scoped_lock.cpp`: Covers `std::scoped_lock`.
- `condition_variable.cpp`: Covers `std::condition_variable`.
- `rwlock.cpp`: Covers the usage of several C++ STL synchronization primitive libraries (`std::shared_mutex`, `std::shared_lock`, `std::unique_lock`) to create a reader-writer's lock implementation. 

### Demo Code for 15-445/645 Bootcamp
- `spring2024/s24_my_ptr.cpp`: Covers the code used in Spring 2024 bootcamp.

## Other Resources
There are many other resources that will be helpful while you get accquainted to C++.
I list a few here!
- [https://en.cppreference.com/w/](https://en.cppreference.com/w/): Unofficial but quite accurate summary and examples of both C++ and C standards.
- [https://cplusplus.com/](https://cplusplus.com/): Contains both a C++ language [tutorial](https://cplusplus.com/doc/tutorial/) and a C++ library [reference](https://cplusplus.com/reference/).
- [Modern C++ Tutorial](https://github.com/changkun/modern-cpp-tutorial). This GitHub repo contains
some information and exercises that are useful!

## Appendix: C++ Documentation for Topics Covered in the Bootcamp
This documentation may be useful to you! It's very comprehensive (much more comprehensive than this
bootcamp) but it may lack some readability. Overall, I think it's still a good idea to try to read
and understand this documentation, especially when working on the projects. Although the bootcamp
tries to be as comprehensive as possible, it still only covers the bare bones of using modern C++.

- [References](https://en.cppreference.com/w/cpp/language/reference)
- [std::move](https://en.cppreference.com/w/cpp/utility/move)
- [Move Constructors](https://en.cppreference.com/w/cpp/language/move_constructor) and [Move Assignment Operators](https://en.cppreference.com/w/cpp/language/move_assignment)
- [Templated Functions](https://en.cppreference.com/w/cpp/language/function_template)
- [Templated Classes](https://en.cppreference.com/w/cpp/language/class_template)
- [Iterators](https://en.cppreference.com/w/cpp/iterator)
- [Namespaces](https://en.cppreference.com/w/cpp/language/namespace)
- [std::vector](https://en.cppreference.com/w/cpp/container/vector)
- [std::set](https://en.cppreference.com/w/cpp/container/set)
- [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)
- [auto](https://en.cppreference.com/w/cpp/language/auto)
- [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
- [std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock)
- [std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
- [std::shared_mutex](https://en.cppreference.com/w/cpp/thread/shared_mutex)
- [std::shared_lock](https://en.cppreference.com/w/cpp/thread/shared_lock)
- [std::unique_lock](https://en.cppreference.com/w/cpp/thread/unique_lock)
