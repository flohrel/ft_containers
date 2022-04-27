#ifndef __MAP_UTILS__H__
# define __MAP_UTILS__H__

# include "libunitcpp.hpp"
# include "map.hpp"
# include <map>
# include <cassert>

namespace unit_test {

namespace map_suite {

/* Equality for containers using a comparison functor */
template< typename Compare >
class value_compare
{
	protected:
		Compare comp;

	public:
		value_compare(Compare c) : comp(c) { }
		~value_compare() { }

		template <typename T, typename U >
		bool operator()( T const& x, U const& y ) const
		{ return (comp(x.first, y.first)); }
};

template< typename T, typename U >
bool operator==(const T& lhs, const U& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return (false);
	}

	typedef typename T::key_compare		compare_type;

	compare_type c = static_cast<compare_type>(rhs.key_comp());				//	Check at compile time that both containers share the same Compare function
	value_compare<compare_type>	comp(c);									//	Initialisation of comparison functor
	
	typename T::const_iterator	first1 = lhs.begin(), last1 = lhs.end();
	typename U::const_iterator	first2 = rhs.begin();

	for (; first1 != last1; first1++, first2++)
	{
		if (comp(*first1, *first2) || comp(*first2, *first1))
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

}	// namespace map_suite
}	// namespace unit_test

#endif