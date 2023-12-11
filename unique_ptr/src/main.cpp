#include <iostream>
#include <unique_ptr.hpp>

int main()
{
    custom::unique_ptr<int> ptr(new int(5));
    auto copy = *ptr;

    auto ptr1(std::move(ptr));
    std::cout << *ptr1 << " " << copy << '\n';

	return 0;
}
