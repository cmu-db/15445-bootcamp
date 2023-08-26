# 15-445/645 C++ Bootcamp
This bootcamp aims to provide a basic introduction to coding in modern C++. 
The features of the C++ language are too vast and expansive to cover in one
bootcamp, and quite frankly, it is learned best through experience. The staff
is certain that 15-445 will make you a more confident C++ programmer! 
However, we do cover some C++ topics that are necessary to know while doing
the programming assignments. This tutorial does not cover basic C/C++ syntax.
It mainly covers C++ programming features, particularly concepts that do not exist in C.

This is the first iteration of the C++ bootcamp for 15-445/645, and feedback
is appreciated!

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

### C++ STL Containers
- `vectors.cpp`: Covers `std::vector`.
- `set.cpp`: Covers `std::set`.
- `unordered_map.cpp`: Covers `std::unordered_map`.

### C++ STL Memory
- `unique_ptr.cpp`: Covers `std::unique_ptr`.
- `shared_ptr.cpp`: Covers `std::shared_ptr`.

### C++ STL Synch Primitives
- `synch_primitives.cpp`: Covers `std::mutex`, `std::scoped_lock`, and `std::condition_variable`.

### Misc
- `wrapper_class.cpp`: Covers C++ wrapper classes.
- `iterator.cpp`: Covers implementing a basic C++ style iterator.
- `auto.cpp`: Covers the usage of the C++ keyword `auto`.
- `namespaces.cpp`: Covers C++ namespaces.

## Other Resources
