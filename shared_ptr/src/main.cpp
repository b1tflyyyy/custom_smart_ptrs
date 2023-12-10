#include <iostream>

#include "stack_allocator.hpp"
#include "shared_ptr.hpp"

#if 0
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
#endif

int main()
{
    custom::shared_ptr<int> ptr = custom::make_shared<int>(555);
    auto ptr1(ptr);

    printf("p1 = %d, p2 = %d\n", *ptr, *ptr1);

	return 0;
}
