#include "header.hpp"

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

void	vector_suite( void )
{
	unit_test::TestSuite	suite("Vector suite");

	suite.push_back(unit_test::TestCase("Constructors", ctor));

	unit_test::MasterSuite::instance().push_back(suite);
}