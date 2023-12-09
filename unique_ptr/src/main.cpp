#include <iostream>
#include <unique_ptr.hpp>

int main()
{
	custom::unique_ptr<int[]> ptr(new int[] { 0 });
	std::cout << *ptr << '\n';

	ptr[0] = 22;
	std::cout << ptr[0] << '\n';

	return 0;
}
