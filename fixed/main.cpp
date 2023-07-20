#include "src/fixed.hpp"
#include <iostream>

int main( void ) 
{
	Fixed<int, 16> a = 256;
	Fixed<float, 16>b(45.76);

	std::cout << a << std::endl;

	a++;

	std::cout << a << std::endl;

	++a;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
}