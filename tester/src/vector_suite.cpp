#include "header.hpp"
#include "vector_utils.hpp"

namespace
{

typedef std::vector<int>	vector_std;
typedef ft::vector<int>		vector_ft;

void	default_ctor( void )
{
	vector_ft	v;
	vector_std	vref;

	assert( v == vref );
}

void	fill_ctor( void )
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	assert( v == vref );
}

void	range_ctor( void )
{
	vector_ft	v_init(42, 42);
	vector_ft	v(v_init.begin(), v_init.end());
	vector_std	vref(v.begin(), v.end());

	assert( v == vref );
}

void	copy_ctor( void )
{
	vector_ft	v_init(42, 42);
	vector_ft	v(v_init);
	vector_std	vref_init(42, 42);
	vector_std	vref(vref_init);

	assert( v == vref );
}

void	equal_op( void )
{
	vector_ft	v_init(42, 42);
	vector_ft	v;
	vector_std	vref(42, 42);

	v = v_init;
	assert( v == vref );
}

void	logical_op( void )
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

void	assign( void )
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
	suite.push_back(unit_test::TestCase("Operator=()", equal_op));
	suite.push_back(unit_test::TestCase("Logical operators", logical_op));
	suite.push_back(unit_test::TestCase("Assign", assign));

	unit_test::MasterSuite::instance().push_back(suite);
}