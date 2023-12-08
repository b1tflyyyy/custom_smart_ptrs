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
    std::allocator<std::uint8_t> alloc;

    auto ptr = custom::sta::make_shared<int>(55);
    auto ptr1 = custom::alc::make_shared<int, decltype(alloc)>(alloc, 56);

    ASSERT_EQ(*ptr, 55);
    ASSERT_EQ(*ptr1, 56);
}

// ============================================= ARRAY SHARED PTR =============================================