#include "cxxtest/TestSuite.h"
#include <vector>
#include "vector.hpp"
#include <iostream>

ft::vector<int> v1;
ft::vector<int>	v2(3, 42);
ft::vector<int>	v3(v2.begin(), v2.end());
ft::vector<int>	v4(v2);

class VectorTestSuite : public CxxTest::TestSuite
{
	public:

		void testConstructor( void )
		{
			// default constructor
			TS_ASSERT_EQUALS(v1.size(), 0);
			// fill constructor
			TS_ASSERT_EQUALS(v2.size(), 3);
			for (ft::vector<int>::const_iterator it = v2.begin(); it != v2.end(); ++it)
				TS_ASSERT_EQUALS(*it, 42);
			TS_ASSERT_EQUALS(v2, v3);
			TS_ASSERT_EQUALS(v2, v4);
		}
};