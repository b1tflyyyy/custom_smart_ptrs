#include <gtest/gtest.h>

#include <shared_ptr.hpp>
#include <memory>

TEST(SharedPtrTests, SharedPtrTests_DEFAULT_MAKE_SHARED_WITH_PARAMS)
{
    auto ptr = custom::sta::make_shared<int>(777);
    const auto expected = 777;

    ASSERT_EQ(*ptr, expected);
}

TEST(SharedPtrTests, SharedPtrTests_ALLOC_MAKE_SHARED_WITH_PARAMS)
{
    std::allocator<std::uint8_t> alloc;
    auto ptr = custom::alc::make_shared<int, decltype(alloc)>(alloc, 777);

    const auto expected = 777;

    ASSERT_EQ(*ptr, expected);
}

TEST(SharedPtrTests, SharedPtrTests_ON_COPY)
{
    auto ptr = custom::sta::make_shared<int>(5);
    auto ptr1(ptr);

    ASSERT_EQ(ptr.get(), ptr1.get());
}

TEST(SharedPtrTests, SharedPtrTests_ON_MOVE_ADDRESS)
{
    auto ptr = custom::sta::make_shared<int>(777);
    int* copy_ptr = ptr.get();

    auto ptr1(std::move(ptr));

    ASSERT_EQ(copy_ptr, ptr1.get());
}

TEST(SharedPtrTests, SharedPtrTests_ON_MOVE_VALUE)
{
    auto ptr = custom::sta::make_shared<int>(777);
    auto ptr1(std::move(ptr));

    const auto expected = 777;

    ASSERT_EQ(*ptr1, expected);
}