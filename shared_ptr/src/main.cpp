#include <iostream>

#include "stack_allocator.hpp"
#include "shared_ptr.hpp"

// TODO: add new tests

// object use 6 gb of memory
struct Object
{
    std::uint8_t array[1'073'741'824] = { 0, 1, 2, 3 };
    std::uint8_t array1[1'073'741'824] = { 0, 1, 2, 3 };
    std::uint8_t array2[1'073'741'824] = { 0, 1, 2, 3 };
    std::uint8_t array3[1'073'741'824] = { 0, 1, 2, 3 };
    std::uint8_t array4[1'073'741'824] = { 0, 1, 2, 3 };
    std::uint8_t array5[1'073'741'824] = { 0, 1, 2, 3 };

    void show()
    {
        for (std::size_t i{}; i < 1'073'741'824; ++i)
        {
            printf("elements: %d, %d, %d, %d, %d, %d\n", array[i], array1[i], array2[i], array3[i], array4[i], array5[i]);
        }
    }

    void fill()
    {
        for (std::size_t i{}; i < 1'073'741'824; ++i)
        {
            array[i] = i;
            array1[i] = i;
            array2[i] = i;
            array3[i] = i;
            array4[i] = i;
            array5[i] = i;
        }
    }
};

__inline void copy_test()
{
    std::allocator<std::uint8_t> alloc;
    
    auto ptr1 = custom::alc::make_shared<Object, decltype(alloc)>(alloc);
    
    auto ptr2(ptr1);
    auto ptr3(ptr1);
    auto ptr4(ptr3); 

    printf("\n=================COPY TEST==================\n");
    printf("ptr1 = %p, ptr2 = %p, ptr3 = %p, ptr4 = %p\n", ptr1.get(), ptr2.get(), ptr3.get(), ptr4.get());
    printf("press any key for continue\n");

    std::cin.get();
}

__inline void move_test()
{
    printf("\n===================MOVE TEST====================\n");
    auto ptr1 = custom::sta::make_shared<Object>();
    auto ptr2(std::move(ptr1));

    printf("ptr2 = %p\n", ptr2.get());
    printf("press any key for continue\n");

    std::cin.get();
}

int main()
{
#if 0
    copy_test();
    move_test();
#endif

    std::allocator<std::uint8_t> alloc;

    custom::shared_ptr<int> ptr = custom::sta::make_shared<int>(6);
    custom::shared_ptr<int[]> ptr1 = custom::sta::make_shared<int[]>(100);
    custom::shared_ptr<int[], decltype(alloc)> ptr2 = custom::alc::make_shared<int[], decltype(alloc)>(alloc, 44);

    std::cin.get();

	return 0;
}
