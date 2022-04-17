#include "header.hpp"

namespace
{

typedef ft::vector<int>	vector;

void	ctor( void )
{
	vector	v1;								// default ctor
	vector	v2(42, 42);						// fill ctor
	vector	v3(v2.begin(), v2.end());		// range ctor
	vector	v4(v2);							// copy ctor
	v1 = v2;								// overload operator=

	assert( v1 == v2 );
	assert( v2 == v3 );
	assert( v3 == v4 );
}

void	iter( void )
{
	vector	v(42, 42);
	size_t	count = 0;

	for (vector::iterator it = v.begin(); it < v.end(); it++)
	{
		(*it) -= count;
		count++;
	}
	assert( count == 42 );
	assert( v[20] == 22 );
}

}

void	vector_suite( void )
{
	unit_test::TestSuite	suite("Vector suite");

	suite.push_back(unit_test::TestCase("Constructors", ctor));
	suite.push_back(unit_test::TestCase("Iterators", iter));

	unit_test::MasterSuite::instance().push_back(suite);
}