#ifndef __VECTOR_UTILS__H__
# define __VECTOR_UTILS__H__

# include "libunitcpp.hpp"
# include "utils/RandomArray.hpp"
# include "vector.hpp"
# include <vector>
# include <cassert>

/**
 * @brief Comparison operator overload
 */
namespace unit_test {

namespace vector_suite {

/* Equality for containers with direct value comparison (vector / stack) */
template< typename T, typename U >
bool operator==(const T& lhs, const U& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return (false);
	}

	typename T::const_iterator	first1 = lhs.begin(), last1 = lhs.end();
	typename U::const_iterator	first2 = rhs.begin();

	for (; first1 != last1; first1++, first2++)
	{
		if (!(*first1 == *first2))
		{
			return (false);
		}
	}
	return (true);
}

template< typename T, typename U >
bool operator!=(const T& lhs, const U& rhs)
{ return (!(lhs == rhs)); }

template< typename T, typename U >
bool operator<(const T& lhs, const U& rhs)
{ return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< typename T, typename U >
bool operator<=(const T& lhs, const U& rhs)
{ return (!(rhs < lhs)); }

template< typename T, typename U >
bool operator>(const T& lhs, const U& rhs)
{ return (rhs < lhs); }

template< typename T, typename U >
bool operator>=(const T& lhs, const U& rhs)
{ return (!(lhs < rhs)); }

}	// namespace vector_suite
}	// namespace unit_test

#endif