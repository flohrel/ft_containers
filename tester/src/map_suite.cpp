# include "map.hpp"
# include <map>

# include "libunitcpp.hpp"

TEST_SUITE(map_suite)

using namespace std;
using namespace unit_test;

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

typedef std::map<std::string, int>										map_std;
typedef ft::map<std::string, int>										map_ft;
typedef	MapGenerator< StringGenerator, RandomGenerator<int> >			mstd_rand;
typedef	MapGenerator< StringGenerator, RandomGenerator<int>, map_ft >	mft_rand;

TEST_CASE(default_ctor)
{
	map_ft	m;
	map_std	mref;

	assert(m == mref);
}

TEST_CASE(range_ctor)
{
	mstd_rand	rmap(1024);
	map_std		minit = rmap();

	map_ft	m(minit.begin(), minit.end());
	map_std	mref(minit.begin(), minit.end());

	assert(m == mref);
}

TEST_CASE(copy_ctor)
{
	mstd_rand	rmap(1024);
	map_std		init_std = rmap();
	map_ft		init_ft(init_std.begin(), init_std.end());

	map_ft	m(init_ft);
	map_std	mref(init_std);

	assert(m == mref);
}

TEST_CASE(equal_op)
{
	mstd_rand	rmap(1024);
	map_std		init_std = rmap();
	map_ft		init_ft(init_std.begin(), init_std.end());

	map_ft	m = init_ft;
	map_std	mref = init_std;

	assert(m == mref);
}

TEST_CASE(logical_op)
{
	{
		map_ft	m;
		map_ft	mref;

		assert( m == mref );
		assert( m <= mref );
		assert( m >= mref );
		assert( !(m != mref) );
		assert( !(m < mref) );
		assert( !(m > mref) );
	}
	{
		mft_rand	rmap(1024);
		map_ft		minit = rmap();

		map_ft		m(minit.begin(), minit.end());
		map_ft		mref(minit.begin(), minit.end());

		assert( m == mref );
		assert( m <= mref );
		assert( m >= mref );
		assert( !(m != mref) );
		assert( !(m < mref) );
		assert( !(m > mref) );
	}
	{
		mft_rand	rmap(1024);
		map_ft		minit = rmap();

		map_ft		m;
		map_ft		mref(minit.begin(), minit.end());

		assert( m != mref );
		assert( m < mref );
		assert( mref > m );
		assert( !(m == mref) );
		assert( !(mref <= m) );
		assert( !(m >= mref) );
	}
}

TEST_CASE(at)
{
}

TEST_CASE(at_op)
{
}

TEST_CASE(iterators)
{
}

TEST_CASE(size)
{
}

TEST_CASE(clear)
{
}

TEST_CASE(insertion)
{
}

TEST_CASE(swap)
{
}

TEST_CASE(count)
{
}

TEST_CASE(find)
{
}

TEST_CASE(equal_range)
{
}

TEST_CASE(bounds)
{
}

TEST_SUITE_END()