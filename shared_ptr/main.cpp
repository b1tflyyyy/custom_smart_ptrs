#include <iostream>
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
	
	custom::shared_ptr<int, stack_allocator<void, 30>> ptr333 = custom::make_shared<int, stack_allocator<void, 30>>(666);
	std::cout << *ptr333 << '\n';
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

	return 0;
}