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

void	at( void )
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
		v.at(42) = 1337;
		assert( false );
	}
	catch(const std::out_of_range& e)
	{
		assert( true );
	}
	catch (...)
	{
		assert( false );
	}
}

void	at_op( void )
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

void	front( void )
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	v.front() = 21;
	vref.front() = 21;
	assert( v[0] == 21 );
	assert( v[0] == vref[0] );
}

void	back( void )
{
	vector_ft	v(42, 42);
	vector_std	vref(42, 42);

	v.back() = 21;
	vref.back() = 21;
	assert( v[41] == vref[41] );
}

void	data( void )
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

}

void	vector_suite( void )
{
	unit_test::TestSuite	suite("Vector suite");

	suite.push_back(unit_test::TestCase("Default ctor", default_ctor));
	suite.push_back(unit_test::TestCase("Fill ctor", fill_ctor));
	suite.push_back(unit_test::TestCase("Range ctor", range_ctor));
	suite.push_back(unit_test::TestCase("Copy ctor", copy_ctor));
	suite.push_back(unit_test::TestCase("Operator=", equal_op));
	suite.push_back(unit_test::TestCase("Logical operators", logical_op));
	suite.push_back(unit_test::TestCase("Assign", assign));
	suite.push_back(unit_test::TestCase("At", at));
	suite.push_back(unit_test::TestCase("Operator[]", at_op));
	suite.push_back(unit_test::TestCase("Front", front));
	suite.push_back(unit_test::TestCase("Back", back));
	suite.push_back(unit_test::TestCase("Data", data));

	unit_test::MasterSuite::instance().push_back(suite);
}