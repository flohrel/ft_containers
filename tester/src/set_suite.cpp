# include "set.hpp"
# include <set>

# include "libunitcpp.hpp"

TEST_SUITE(set_suite)

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
		{ return (comp(x, y)); }
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

typedef std::set<std::string>										set_std;
typedef ft::set<std::string>										set_ft;
typedef	SetGenerator< StringGenerator >								sstd_rand;
typedef	SetGenerator< StringGenerator, set_ft >						sft_rand;

TEST_CASE(default_ctor)
{
	set_ft	m;
	set_std	mref;

	assert(m == mref);
}

TEST_CASE(range_ctor)
{
	sstd_rand	rset(1024);
	set_std		minit = rset();

	set_ft	m(minit.begin(), minit.end());
	set_std	mref(minit.begin(), minit.end());

	assert(m == mref);
}

TEST_CASE(copy_ctor)
{
	sstd_rand	rset(1024);
	set_std		init_std = rset();
	set_ft		init_ft(init_std.begin(), init_std.end());

	set_ft	m(init_ft);
	set_std	mref(init_std);

	assert(m == mref);
}

TEST_CASE(equal_op)
{
	sstd_rand	rset(1024);
	set_std		init_std = rset();
	set_ft		init_ft(init_std.begin(), init_std.end());

	set_ft	m = init_ft;
	set_std	mref = init_std;

	assert(m == mref);
}

TEST_CASE(logical_op)
{
	{
		set_ft	m;
		set_ft	mref;

		assert( m == mref );
		assert( m <= mref );
		assert( m >= mref );
		assert( !(m != mref) );
		assert( !(m < mref) );
		assert( !(m > mref) );
	}
	{
		sft_rand	rset(1024);
		set_ft		minit = rset();

		set_ft		m(minit.begin(), minit.end());
		set_ft		mref(minit.begin(), minit.end());

		assert( m == mref );
		assert( m <= mref );
		assert( m >= mref );
		assert( !(m != mref) );
		assert( !(m < mref) );
		assert( !(m > mref) );
	}
	{
		sft_rand	rset(1024);
		set_ft		minit = rset();

		set_ft		m;
		set_ft		mref(minit.begin(), minit.end());

		assert( m != mref );
		assert( m < mref );
		assert( mref > m );
		assert( !(m == mref) );
		assert( !(mref <= m) );
		assert( !(m >= mref) );
	}
}

TEST_CASE(iterators)
{
	set_ft	m;
	set_std	mref;

	m.insert("foo");
	mref.insert("foo");
	m.insert("bar");
	mref.insert("bar");
	m.insert("baz");
	mref.insert("baz");

	set_ft::iterator it = m.begin();
	set_ft::const_iterator cit = m.begin();
	set_ft::reverse_iterator rit = m.rbegin();
	set_ft::const_reverse_iterator crit = m.rbegin();
	set_ft::iterator eit = m.end();
	set_ft::reverse_iterator reit = m.rend();
	set_std::iterator it_ref = mref.begin();
	set_std::const_iterator cit_ref = mref.begin();
	set_std::reverse_iterator rit_ref = mref.rbegin();
	set_std::const_reverse_iterator crit_ref = mref.rbegin();
	set_std::iterator eit_ref = mref.end();
	set_std::reverse_iterator reit_ref = mref.rend();

	assert( *cit == *cit_ref );
	assert( *crit == *crit_ref );
	while (it != m.end())
	{
		assert( *it == *it_ref++ );
		assert( *it++ == *(--reit_ref) );
		assert( *rit == *rit_ref++ );
		assert( *rit++ == *(--eit_ref) );
	}
}

TEST_CASE(size)
{
	sft_rand	rand(1024);
	set_ft		m = rand();

	assert( m.size() == 1024 );
}

TEST_CASE(clear)
{
	sft_rand	rand(1024);
	set_ft		m = rand();

	m.clear();
	assert( m.empty() );
}

TEST_CASE(insertion)
{
	sstd_rand				mrand(1024);
	set_std					mref = mrand();
	set_std::iterator cit = mref.begin();
	set_ft					m;
	set_std					mstd;

	for (size_t i = 0; i < 1024; i++)
	{
		m.insert(*cit);
		cit++;
	}
	assert( m == mref );

	cit = mref.begin();
	set_ft::iterator	cit2 = m.begin();
	for (size_t i = 0; i < 1024; i++)
	{
		if (i % 2)
		{
			m.erase(cit2);
			mref.erase(cit);
		}
		cit++;
		cit2++;
	}
	assert( m == mref );
}

TEST_CASE(swap)
{
	sft_rand	mrand(1024);
	set_ft		m1 = mrand();
	set_ft		m2 = mrand();
	set_ft		m1_copy = m1;
	set_ft		m2_copy = m2;

	assert( m1 == m1_copy );
	assert( m2 == m2_copy );
	m1.swap(m2);
	assert( m1 == m2_copy );
	assert( m2 == m1_copy );
}

TEST_CASE(count)
{
	sft_rand	mrand(1024);
	set_ft		m = mrand();

	assert( m.size() == 1024 );

	set_ft::iterator	it = m.begin();
	for (size_t i = 0; i < 10; i++)
	{
		it++;
	}
	m.erase( m.begin(), it );
	assert( m.size() == (1024 - 10) );

	m.clear();
	assert( m.size() == 0 );
}

TEST_CASE(find)
{
	set_ft	m;
	set_std	mref;

	m.insert("foo");
	mref.insert("foo");
	m.insert("bar");
	mref.insert("bar");
	m.insert("baz");
	mref.insert("baz");

	assert( m.find("foo") != m.end() );
	assert( m.find("truc") == m.end() );
}

TEST_SUITE_END()