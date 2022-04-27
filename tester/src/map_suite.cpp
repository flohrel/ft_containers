# include "map_utils.hpp"

namespace unit_test { 

namespace map_suite {

typedef std::map<std::string, int>										map_std;
typedef ft::map<std::string, int>										map_ft;
typedef	MapGenerator< StringGenerator, RandomGenerator<int> >			mstd_rand;
typedef	MapGenerator< StringGenerator, RandomGenerator<int>, map_ft >	mft_rand;

void	default_ctor( void )
{
	map_ft	m;
	map_std	mref;

	assert(m == mref);
}

void	range_ctor( void )
{
	mstd_rand	rmap(1024);
	map_std		minit = rmap();

	map_ft	m(minit.begin(), minit.end());
	map_std	mref(minit.begin(), minit.end());

	assert(m == mref);
}

void	copy_ctor( void )
{
	mstd_rand	rmap(1024);
	map_std		init_std = rmap();
	map_ft		init_ft(init_std.begin(), init_std.end());

	map_ft	m(init_ft);
	map_std	mref(init_std);

	assert(m == mref);
}

void	equal_op( void )
{
	mstd_rand	rmap(1024);
	map_std		init_std = rmap();
	map_ft		init_ft(init_std.begin(), init_std.end());

	map_ft	m = init_ft;
	map_std	mref = init_std;

	assert(m == mref);
}

void	logical_op( void )
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

void	at( void )
{
}

void	at_op( void )
{
}

void	iterators( void )
{
}

void	size( void )
{
}

void	clear( void )
{
}

void	insertion( void )
{
}

void	swap( void )
{
}

void	count( void )
{
}

void	find( void )
{
}

void	equal_range( void )
{
}

void	bounds( void )
{
}

void	suite_registrar( void )
{
	TestSuite	suite("Map suite");

	suite.push_back(TestCase("Default ctor", default_ctor));
	suite.push_back(TestCase("Range ctor", range_ctor));
	suite.push_back(TestCase("Copy ctor", copy_ctor));
	suite.push_back(TestCase("Operator=", equal_op));
	suite.push_back(TestCase("Logical operators", logical_op));
	suite.push_back(TestCase("At", at));
	suite.push_back(TestCase("Operator[]", at_op));
	suite.push_back(TestCase("Iterators", iterators));
	suite.push_back(TestCase("Size", size));
	suite.push_back(TestCase("Clear", clear));
	suite.push_back(TestCase("Insertion", insertion));
	suite.push_back(TestCase("Swap", swap));
	suite.push_back(TestCase("Count", count));
	suite.push_back(TestCase("Find", find));
	suite.push_back(TestCase("Equal range", equal_range));
	suite.push_back(TestCase("Lower/upper bound", bounds));

	MasterSuite::instance().push_back(suite);
}

}	// namespace map_suite
}	// namespace unit_test