#include "cxxtest/TestSuite.h"
#include "map.hpp"

ft::map<std::string, int>	map1;
ft::map<std::string, int>	map2;

class MapTestSuite : public CxxTest::TestSuite
{
	public:

		void	testConstructor(void)
		{
			TS_ASSERT_EQUALS(map1.size(), 0);
		}

		void	testEqualOperator(void)
		{
			map2 = map1;
			TS_ASSERT_EQUALS(map1.size(), map2.size());
		}

};