#include <iostream>
#include <stack>
#include "stack_allocator.hpp"
#include "shared_ptr.hpp"

// TODO: add logs in Makefile
//

int main()
{
#if 0
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr(new int(5));
	std::cout << "\n*ptr.get() = " << *ptr.get() << '\n';
	
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr1(ptr);
	std::cout << "*ptr1.get() = " << *ptr1 << "\n\n"; 
#endif	
	
#if 0
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr333 = custom::make_shared<int, stack_allocator<void, 30>>(666);
	std::cout << *ptr333 << '\n';

	custom::shared_ptr<int, stack_allocator<void, 30>> pt;
	pt = ptr333;

	custom::shared_ptr<int, stack_allocator<void, 30>> ptr777(std::move(pt));
	std::cout << *ptr777 << '\n';
	std::cout << "count of ptrs = " << ptr777.use_count() << '\n';
#endif
	// std::cout << "copy: " << *pt << '\n';
#if 0
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr100(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr2(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr3(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr4(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr5(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr6(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr7(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr8(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr9(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr10(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr11(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr12(ptr);
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr13(ptr);
#endif
    stack_allocator<void, 500> allocator;  
    std::cout << "used memory " << allocator.get_memory_used() << '\n';
    
    // stack_allocator<void, 400> alloc;
    auto ptr = custom::alc::make_shared<int, decltype(allocator)>(allocator, 24);
    std::cout << *ptr << '\n';
    std::cout << "used memory " << allocator.get_memory_used() << '\n';
    
    *ptr = 77;
    std::cout << *ptr << '\n';

	return 0;
}
