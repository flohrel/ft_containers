#include "header.hpp"
#include <vector>

typedef std::vector<int>	vector_std;
typedef ft::vector<int>		vector_ft;

namespace
{

void	default_ctor( void )
{
	vector_ft	v;
	vector_std	vref;

	assert( v.size() == vref.size() );
}

void	fill_ctor( void )
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	assert( v.size() == vref.size() );
	for (int i = 0; i < 42; i++)
	{
		assert( v[i] == vref[i] );
	}
}

void	range_ctor( void )
{
	vector_ft	v_init(42, 42);
	vector_ft	v(v_init.begin(), v_init.end());
	vector_std	vref(v.begin(), v.end());

	assert( v.size() == vref.size() );
	for (int i = 0; i < 42; i++)
	{
		assert( v[i] == vref[i] );
	}
}

void	copy_ctor( void )
{
	vector_ft	v_init(42, 42);
	vector_ft	v(v_init);
	vector_std	vref_init(42, 42);
	vector_std	vref(vref_init);

	assert( v.size() == vref.size() );
	for (int i = 0; i < 42; i++)
	{
		assert( v[i] == vref[i] );
	}
}

void	equal_op( void )
{
	vector_ft	v_init(42, 42);
	vector_ft	v;
	vector_std	vref(42, 42);

	v = v_init;
	assert( v.size() == vref.size() );
	for (int i = 0; i < 42; i++)
	{
		assert( v[i] == vref[i] );
	}
}

// void	iter( void )
// {
// 	vector_ft	v1(42, 42);
// 	vector_std	v2(42, 42);

// 	size_t		count = 0;

// 	vector_ft::iterator it1 = v1.begin();
// 	vector_std::iterator it2 = v2.begin();

// 	for (; it1 != v1.end(); it1++, it2++)
// 	{
// 		(*it1) -= count;
// 		(*it2) -= count;
// 		count++;
// 	}
// 	assert( v1[20] == 22 );
// }

}

void	vector_suite( void )
{
	unit_test::TestSuite	suite("Vector suite");

	suite.push_back(unit_test::TestCase("Default constructor", default_ctor));
	suite.push_back(unit_test::TestCase("Fill constructor", fill_ctor));
	suite.push_back(unit_test::TestCase("Range constructor", range_ctor));
	suite.push_back(unit_test::TestCase("Copy constructor", copy_ctor));
	suite.push_back(unit_test::TestCase("Operator=() overload", equal_op));
	// suite.push_back(unit_test::TestCase("Iterators", iter));

	unit_test::MasterSuite::instance().push_back(suite);
}