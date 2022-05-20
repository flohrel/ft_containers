# include "stack.hpp"
# include <stack>

# include "libunitcpp.hpp"

TEST_SUITE(stack_suite)

using namespace std;
using namespace unit_test;

template< class T >
class MutantStackSTD: public std::stack<T>
{
	public:
		typedef typename std::stack<T>::container_type::iterator				iterator;
		typedef typename std::stack<T>::container_type::const_iterator			const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator		reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

		iterator				begin( void ) { return std::stack<T>::c.begin(); };
		const_iterator			begin( void ) const { return std::stack<T>::c.begin(); };
		iterator				end( void ) { return std::stack<T>::c.end(); };
		const_iterator			end( void ) const { return std::stack<T>::c.end(); };
		reverse_iterator		rbegin( void ) { return std::stack<T>::c.rbegin(); };
		const_reverse_iterator	rbegin( void ) const { return std::stack<T>::c.rbegin(); };
		reverse_iterator		rend( void ) { return std::stack<T>::c.rend(); };
		const_reverse_iterator	rend( void ) const { return std::stack<T>::c.rend(); };
		size_t					size( void ) const { return std::stack<T>::c.size(); };
};

template< class T >
class MutantStackFT: public ft::stack<T>
{
	public:
		typedef typename ft::stack<T>::container_type::iterator					iterator;
		typedef typename ft::stack<T>::container_type::const_iterator			const_iterator;
		typedef typename ft::stack<T>::container_type::reverse_iterator			reverse_iterator;
		typedef typename ft::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

		iterator				begin( void ) { return ft::stack<T>::c.begin(); };
		const_iterator			begin( void ) const { return ft::stack<T>::c.begin(); };
		iterator				end( void ) { return ft::stack<T>::c.end(); };
		const_iterator			end( void ) const { return ft::stack<T>::c.end(); };
		reverse_iterator		rbegin( void ) { return ft::stack<T>::c.rbegin(); };
		const_reverse_iterator	rbegin( void ) const { return ft::stack<T>::c.rbegin(); };
		reverse_iterator		rend( void ) { return ft::stack<T>::c.rend(); };
		const_reverse_iterator	rend( void ) const { return ft::stack<T>::c.rend(); };
		size_t					size( void ) const { return ft::stack<T>::c.size(); };
};

typedef MutantStackSTD<int>					stack_std;
typedef MutantStackFT<int>					stack_ft;

/* Equality for containers with direct value comparison */
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

TEST_CASE(ctor) {
	stack_ft							s1;
	stack_std							sref;
	std::deque<int>						d;
	ft::stack<int, std::deque<int> >	s2(d);

	assert( s1 == sref );
}

TEST_CASE(miscellaneous) {
	stack_ft	s;
	stack_std	sref;

	assert( s.empty() == true );

	for (size_t i = 0; i != 65536; i ++)
	{
		s.push(i);
		sref.push(i);
	}
	assert( s == sref );

	s.pop();
	sref.pop();
	assert( s.top() == sref.top() );
}

TEST_SUITE_END()