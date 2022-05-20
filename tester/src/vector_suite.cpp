# include "vector.hpp"
# include <vector>

# include "libunitcpp.hpp"

TEST_SUITE(vector_suite)

using namespace std;
using namespace unit_test;

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

typedef std::vector<int>					vector_std;
typedef ft::vector<int>						vector_ft;

TEST_CASE(default_ctor)
{
	vector_ft	v;
	vector_std	vref;

	assert( v == vref );
}

TEST_CASE(fill_ctor)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	assert( v == vref );
}

TEST_CASE(range_ctor)
{
	vector_ft	v_init(42, 42);
	vector_ft	v(v_init.begin(), v_init.end());
	vector_std	vref(v.begin(), v.end());

	assert( v == vref );
}

TEST_CASE(copy_ctor)
{
	vector_ft	v_init(42, 42);
	vector_ft	v(v_init);
	vector_std	vref_init(42, 42);
	vector_std	vref(vref_init);

	assert( v == vref );
}

TEST_CASE(equal_op)
{
	vector_ft	v_init(42, 42);
	vector_ft	v;
	vector_std	vref(42, 42);

	v = v_init;
	assert( v == vref );
}

TEST_CASE(logical_op)
{
	{
		vector_ft	v;
		vector_std	vref;

		assert( v == vref );
		assert( v <= vref );
		assert( v >= vref );
		assert( !(v != vref) );
		assert( !(v < vref) );
		assert( !(v > vref) );
	}
	{
		vector_ft	v(42, 42);
		vector_std	vref(42, 42);

		assert( v == vref );
		assert( v <= vref );
		assert( v >= vref );
		assert( !(v != vref) );
		assert( !(v < vref) );
		assert( !(v > vref) );
	}
	{
		vector_ft	v;
		vector_std	vref(42, 42);

		assert( v != vref );
		assert( v < vref );
		assert( vref > v );
		assert( !(v == vref) );
		assert( !(vref <= v) );
		assert( !(v >= vref) );
	}
}

TEST_CASE(assign)
{
	vector_ft	v;
	vector_std	vref;

	v.assign(666, 666);
	vref.assign(666, 666);
	assert( v.size() == vref.size() );

	v.assign(0, 0);
	vref.assign(0, 0);
	assert( v.size() == vref.size() );

	v.assign(42024, 1337);
	vref.assign(42024, 1337);
	assert( v.size() == vref.size() );

	vector_std	v_assign(42, 42);

	v.assign(v_assign.begin(), v_assign.end());
	vref.assign(v_assign.begin(), v_assign.end());
	assert( v.size() == vref.size() );
}

TEST_CASE(at)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	assert( v.at(21) == vref.at(21) );
	for (int i = 41; i != 0; i--)
	{
		v.at(i) -= i;
		vref.at(i) -= i;
		assert( v.at(i) == vref.at(i) );
	}
	try
	{
		v.at(43) = 1337;
		assert( false );
	}
	catch (const std::out_of_range& e)
	{
		assert( true );
	}
	catch (...)
	{
		assert( false );
	}
}

TEST_CASE(at_op)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	assert( v[21] == vref[21] );
	for (int i = 41; i != 0; i--)
	{
		v[i] -= i;
		vref[i] -= i;
		assert( v[i] == vref[i] );
	}
}

TEST_CASE(front)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	v.front() = 21;
	vref.front() = 21;
	assert( v[0] == 21 );
	assert( v[0] == vref[0] );
}

TEST_CASE(back)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	v.back() = 21;
	vref.back() = 21;
	assert( v[41] == vref[41] );
}

TEST_CASE(data)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	int	*ptr = v.data();
	int	*ptr_ref = vref.data();

	for (size_t i = 0; i != v.size(); i++)
	{
		assert( *(ptr + i) == *(ptr_ref + i) );
	}
}

TEST_CASE(iterators)
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	for (int i = 41; i != 0; i--)
	{
		v[i] *= i;
		vref[i] *= i;
	}

	vector_ft::iterator it = v.begin();
	vector_ft::const_iterator cit = v.begin();
	vector_ft::reverse_iterator rit = v.rbegin();
	vector_ft::const_reverse_iterator crit = v.rbegin();
	vector_ft::iterator eit = v.end();
	vector_ft::reverse_iterator reit = v.rend();
	vector_std::iterator it_ref = vref.begin();
	vector_std::const_iterator cit_ref = vref.begin();
	vector_std::reverse_iterator rit_ref = vref.rbegin();
	vector_std::const_reverse_iterator crit_ref = vref.rbegin();
	vector_std::iterator eit_ref = vref.end();
	vector_std::reverse_iterator reit_ref = vref.rend();

	assert( (*cit) == (*cit_ref) );
	assert( (*crit) == (*crit_ref) );
	while (it != v.end())
	{
		assert( (*it) == (*(it_ref++)) );
		assert( (*it++) == (*(--reit_ref)) );
		assert( (*rit) == (*rit_ref++) );
		assert( (*rit++) == (*(--eit_ref)) );
	}
}

TEST_CASE(size)
{
	vector_ft	v;

	assert( v.empty() == true );

	v = vector_ft(666, 666);
	assert( v.size() == 666 );
	assert( v.empty() == false );

	vector_std					vref;
	vector_ft::allocator_type	alloc = v.get_allocator();
	vector_std::allocator_type	alloc_ref = vref.get_allocator();

	assert( alloc.max_size() == alloc_ref.max_size() );

	size_t old_capacity = v.capacity();
	v.reserve(1337);
	assert( v.capacity() > old_capacity );
	assert( v.size() == 666 );

	try
	{
		v.reserve(v.max_size());
		assert( false );
	}
	catch (const std::length_error& e)
	{
		assert( true );
	}
	catch (...)
	{
		assert( false );
	}
}

TEST_CASE(clear)
{
	vector_ft	v(666, 666);

	size_t old_capacity = v.capacity();
	v.clear();
	assert( v.capacity() == old_capacity );
	assert( v.empty() == true );
}

TEST_CASE(insertion)
{
	vector_ft	v;
	vector_std	vref;

	v.insert(v.begin(), 1337);
	vref.insert(vref.begin(), 1337);
	assert( v == vref );

	size_t count = v.capacity() - v.size();
	v.insert(v.begin(), count, 42);
	vref.insert(vref.begin(), count, 42);
	assert( v == vref );

	count = v.capacity() - v.size();
	v.insert(v.begin(), count, 666);
	vref.insert(vref.begin(), count, 666);
	assert( v == vref );

	vector_std	array(65536, RandomGenerator<int>());
	for (int i = 1; i < 16; i++)
	{
		v.insert(v.begin(), array.begin() + (i * 4), array.begin() + (i * 8));
		v.push_back(*(array.end() - i * 16));
		vref.insert(vref.begin(), array.begin() + (i * 4), array.begin() + (i * 8));
		vref.push_back(*(array.end() - i * 16));
	}
	v.resize(v.size() / 2);
	vref.resize(vref.size() / 2);
	assert( v == vref );

	for (int i = 1; i < 16; i++)
	{
		v.insert(v.end(), array.begin() + i, array.begin() + (i * 16));
		v.push_back(*(array.begin() + i * 16));
		vref.insert(vref.end(), array.begin() + i, array.begin() + (i * 16));
		vref.push_back(*(array.begin() + i * 16));
	}
	assert( v == vref );

	for (int i = 1; i < 16; i++)
	{
		v.pop_back();
		v.erase(v.begin() + (2 * i));
		v.insert(v.begin() + (2 * i), array.begin(), array.end() - (i * 32));
		v.erase(v.end() - (i * 4), v.end());
		vref.pop_back();
		vref.erase(vref.begin() + (2 * i));
		vref.insert(vref.begin() + (2 * i), array.begin(), array.end() - (i * 32));
		vref.erase(vref.end() - (i * 4), vref.end());
	}
	v.resize(v.size() * 2);
	vref.resize(vref.size() * 2);
	assert( v == vref );
}

TEST_SUITE_END()