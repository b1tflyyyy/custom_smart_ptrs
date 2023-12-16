## Educational Project 

## Goal of the project:
This project was created to show a simple implementation of smart_ptrs it includes implementations of unique_ptr and shared_ptr.

## Tech Stack:
- CMake
- C++ 20 
- Google Test Framework

## Requirements
- C++ >= 20
- CMake >= 3.14

## Support status on systems:
- [x] Windows 
- [x] Linux

## Code Samples
- shared pointer
```cpp
// shared pointer at default use stack_allocator for control block
// you can change default stack_allocator

// create shared pointer
custom::shared_ptr<int> ptr(new int(555));
auto ptr1(ptr); // value 555

// create shared pointer using make_shared
auto ptr2 = custom::make_shared<int>(55);
auto ptr3(std::move(ptr2)); // ptr2 -> nullptr, ptr3 -> 55

// create shared pointer with custom deleter
std::allocator<int> alloc;
int* num = alloc.allocate(1);

*num = 55;
custom::shared_ptr<int> ptr(num, [&alloc](int* ptr) -> void { alloc.deallocate(ptr, 1); });

// You can do the same with a shared pointer where T is array
// For example:
custom::shared_ptr<int[]> ptr(new int[5] { 1, 2, 3, 4, 5 });
auto ptr1(ptr); // ptr1 -> 1, 2, 3, 4, 5
```

- unique pointer
```cpp
// create unique pointer
custom::unique_ptr<int> ptr(new int(5));
auto ptr1(ptr); // CE!

// create unique pointer using make_unique
auto ptr2 = custom::make_unique<int>(5);
auto ptr3(std::move(ptr2)); // ptr2 -> nullptr, ptr3 -> 5

// create unique pointer with custom deleter
std::allocator<int> alloc;

custom::unique_ptr<int> ptr(alloc.allocate(1), [&alloc](int* ptr) -> void { alloc.deallocate(ptr, 1); });
*ptr = 55;

// You can do the same with a unique pointer where T is array
// For example:
custom::unique_ptr<int[]> ptr(new int[3] { 1, 2, 3 });
auto ptr1(ptr); // CE!
```