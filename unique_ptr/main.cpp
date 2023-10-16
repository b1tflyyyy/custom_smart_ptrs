#include <iostream>
#include "unique_ptr.hpp"

int main()
{
	custom::unique_ptr<int> ptr(new int(5));
	
	std::cout << "ptr1: " << ptr.get() << '\n';
	std::cout << *ptr << '\n';
	
	custom::unique_ptr<int> ptr2(std::move(ptr));
	std::cout << "ptr2: " <<ptr2.get() << '\n';

	std::cout << "ptr after move: " << ptr.get() << '\n';


	if (ptr)
	{
		std::cout << "pointer is not nullptr\n";
	}
	else
	{
		std::cout << "pointer is nullptr\n";
	}


	return 0;
}
