#include <gtest/gtest.h>

#include <unique_ptr.hpp>
#include <memory>

// ============================================= DEFAULT UNIQUE PTR =============================================
TEST(UniquePtrTests, UniquePtrDefaultTests_CTOR_MOVE_OPERATORS)
{
    custom::unique_ptr<int> ptr(new int(5));
    auto copy = *ptr;

    auto ptr1(std::move(ptr));

    ASSERT_EQ(copy, *ptr1);
}

TEST(UniquePtrTests, UniquePtrDefaultTests_CUSTOM_DELETER)
{
    std::allocator<int> alloc;

    custom::unique_ptr<int> ptr(alloc.allocate(1), [&alloc](int* ptr) -> void { alloc.deallocate(ptr, 1); });
    *ptr = 55;

    auto ptr1(std::move(ptr));

    ASSERT_EQ(55, *ptr1);
}

TEST(UniquePtrTests, UniquePtrDefaultTests_BOOL_OPERATOR_GET)
{
    custom::unique_ptr<int> ptr(new int(5));

    if (ptr)
    {
        ptr.get();
        return;
    }

    FAIL();
}

// ============================================= ARRAY UNIQUE PTR =============================================
TEST(UniquePtrTests, UniquePtrArrayTests_CTOR_MOVE_OPERATORS)
{
    custom::unique_ptr<int[]> ptr(new int[3] { 1, 2, 3 });
    auto ptr1(std::move(ptr));

    ASSERT_EQ(ptr1[0], 1);
    ASSERT_EQ(ptr1[1], 2);
    ASSERT_EQ(ptr1[2], 3);
}

TEST(UniquePtrTests, UniquePtrArrayTests_CUSTOM_DELETER)
{
    std::allocator<int> alloc;

    custom::unique_ptr<int[]> ptr(alloc.allocate(3), [&alloc](int* ptr) -> void { alloc.deallocate(ptr, 3); });

    ptr[0] = 0;
    ptr[1] = 1;
    ptr[2] = 2;

    auto ptr1(std::move(ptr));

    ASSERT_EQ(ptr1[0], 0);
    ASSERT_EQ(ptr1[1], 1);
    ASSERT_EQ(ptr1[2], 2);
}

TEST(UniquePtrTests, UniquePtrArrayTests_BOOL_OPERATOR_GET)
{
    custom::unique_ptr<int[]> ptr(new int[3] { 1, 2, 3 });

    if (ptr)
    {
        ptr.get();
        return;
    }

    FAIL();
}