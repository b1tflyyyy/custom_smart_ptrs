#include <iostream>
#include "custom_allocator.hpp"

int main()
{
	custom_allocator<int, 20> allocator;
	auto ptr = allocator.allocate(0);

	*ptr = 12;
	std::cout << *ptr << '\n';

	auto ptr1 = allocator.allocate(0);
	*ptr1 = 22;

	std::cout <<  *ptr1 << '\n'; 


	return 0;
}
