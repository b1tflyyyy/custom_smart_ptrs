#include <iostream>
#include <stack>
#include "stack_allocator.hpp"
#include "shared_ptr.hpp"

// TODO: add logs in Makefile
//

__inline void copy_test()
{
    stack_allocator alloc;
    
    auto ptr1 = custom::alc::make_shared<int, decltype(alloc), true>(alloc, 777);
    
    auto ptr2(ptr1);
    auto ptr3(ptr1);
    auto ptr4(ptr3); 

    printf("\n=================COPY TEST==================\n");
    printf("ptr1 = %d, ptr2 = %d, ptr3 = %d, ptr4 = %d\n", *ptr1, *ptr2, *ptr3, *ptr4);
}

__inline void move_test()
{
    printf("\n===================MOVE TEST====================\n");
    auto ptr1 = custom::sta::make_shared<int>(33);
    auto ptr2(std::move(ptr1));

    printf("ptr2 = %d\n", *ptr2);
}

int main()
{
    copy_test();
    move_test();

	return 0;
}
