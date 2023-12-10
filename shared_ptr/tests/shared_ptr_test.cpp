#include <gtest/gtest.h>

#include <shared_ptr.hpp>
#include <memory>

// ============================================= DEFAULT SHARED PTR =============================================
TEST(SharedPtrTests, SharedPtrTests_COPY)
{
    custom::shared_ptr<int> ptr(new int(555));
    auto ptr1(ptr);

    ASSERT_EQ(*ptr, *ptr1);
    ASSERT_EQ(ptr.get(), ptr1.get());
    ASSERT_EQ(ptr.use_count(), 2);
}

TEST(SharedPtrTests, SharedPtrTests_CUSTOM_ALLOC_DELETER)
{
    std::allocator<int> alloc;
    int* num = alloc.allocate(sizeof(int));
    *num = 55;

    custom::shared_ptr<int> ptr(num, [&alloc](int* ptr, std::size_t sz) -> void { alloc.deallocate(ptr, sz); });

    { auto ptr2(ptr); }
    auto ptr1(ptr);

    ASSERT_EQ(*ptr, *ptr1);
    ASSERT_EQ(ptr.get(), ptr1.get());
    ASSERT_EQ(ptr.use_count(), 2);
}

TEST(SharedPtrTests, SharedPtrTests_MAKE_SHARED)
{
    auto ptr = custom::sta::make_shared<int>(55);
    ASSERT_EQ(*ptr, 55);
}

// ============================================= ARRAY SHARED PTR =============================================
TEST(SharedPtrTests, SharedPtrArrayTests_COPY)
{
    custom::shared_ptr<int[]> ptr(new int[5] { 1, 2, 3, 4, 5 });
    auto ptr1(ptr);

    ASSERT_EQ(*ptr, *ptr1);
    ASSERT_EQ(ptr[1], ptr[1]);
    ASSERT_EQ(ptr[2], ptr[2]);
    ASSERT_EQ(ptr[3], ptr1[3]);
    ASSERT_EQ(ptr[4], ptr1[4]);

    ASSERT_EQ(ptr.get(), ptr1.get());
    ASSERT_EQ(ptr.use_count(), 2);
}

TEST(SharedPtrTests, SharedPtrArrayTests_CUSTOM_ALLOC_DELETER)
{
    std::allocator<int> alloc;
    int* num = alloc.allocate(sizeof(int) * 3);

    num[0] = 55;
    num[1] = 77;
    num[2] = 88;

    custom::shared_ptr<int[]> ptr(num, [&alloc](int* ptr) -> void { alloc.deallocate(ptr, sizeof(int) * 3); });

    { auto ptr2(ptr); }
    auto ptr1(ptr);

    ASSERT_EQ(ptr[0], ptr1[0]);
    ASSERT_EQ(ptr[1], ptr1[1]);
    ASSERT_EQ(ptr[2], ptr1[2]);

    ASSERT_EQ(ptr.get(), ptr1.get());
    ASSERT_EQ(ptr.use_count(), 2);
}

TEST(SharedPtrTests, SharedPtrArrayTests_MAKE_SHARED)
{
    auto ptr = custom::sta::make_shared<int[]>(3);

    ptr[0] = 1;
    ptr[1] = 2;
    ptr[2] = 3;

    ASSERT_EQ(ptr[0], 1);
    ASSERT_EQ(ptr[1], 2);
    ASSERT_EQ(ptr[2], 3);
}