#include <gtest/gtest.h>

#include <stack_allocator.hpp>

class TestObject
{
public:
    std::uint8_t array[1'000] = { 0 };
};

TEST(StackAllocatorTests, StackAllocatorTests_ALLOCATE_MEMORY_ONE)
{
    stack_allocator<void, 200> alloc;
    int* ptr = static_cast<int*>(alloc.allocate(sizeof(int)));

    ASSERT_NE(ptr, nullptr);
}

TEST(StackAllocatorTests, StackAllocatorTests_ALLOCATE_MEMORY_TWO)
{
    stack_allocator<void, 200> alloc;
    double* ptr = static_cast<double*>(alloc.allocate(sizeof(double)));

    ASSERT_NE(ptr, nullptr);
}

TEST(StackAllocatorTests, StackAllocatorTests_ALLOCATE_MEMORY_THREE)
{
    stack_allocator<void, 2000> alloc;
    TestObject* ptr = static_cast<TestObject*>(alloc.allocate(sizeof(TestObject)));

    ASSERT_NE(ptr, nullptr);
}

