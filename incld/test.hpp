#include "cxxtest/TestSuite.h"
#include <vector>
#include "vector.hpp"
#include <iostream>

ft::vector<int> v1;
ft::vector<int>	v2(3, 0);
ft::vector<int>	v3(v2.begin(), v2.end());

class VectorTestSuite : public CxxTest::TestSuite
{
	public:

		void testConstructor( void )
		{
			TS_ASSERT_EQUALS(v1.size(), 0);
			TS_ASSERT_EQUALS(v2.size(), 3);
			TS_ASSERT_EQUALS(v2, v3);
		}
};