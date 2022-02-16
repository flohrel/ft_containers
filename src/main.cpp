#include "vector.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#include <iterator>
#include <vector>

int	main(void)
{
	ft::vector<int> foo(3, 0);

	for (ft::vector<int>::iterator it = foo.begin(); it != foo.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	
	return (0);
}