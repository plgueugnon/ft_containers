#include <iostream>
#include "ft_enable_if.hpp"
#include "ft_random_access_iterator.hpp"
#include <vector>
#include <algorithm>

int	main(void)
{
	ft::random_access_iterator<int> a;
	ft::random_access_iterator<const int> c;
	ft::random_access_iterator<int> b(a);

	ft::random_access_iterator<char> d;
	ft::random_access_iterator<const char> e;

	ft::random_access_iterator<char> z;

	if (d == z)
		std::cout << "is equal !" << std::endl;
	if (d != z)
		std::cout << "is not equal !" << std::endl;

	ft::random_access_iterator<float> y;
	std::cout << d - z << std::endl;

	std::vector<float>	tab;
	std::vector<float>::iterator beg = tab.begin();
	std::vector<float>::iterator end = tab.end();
	end - beg; // compile avec des types float ?

	return (0);
}