#include "cxxtest/TestSuite.h"
#include "map.hpp"

ft::map<std::string, int>	map1;

class MapTestSuite : public CxxTest::TestSuite
{
	public:

		void	testConstructor(void)
		{
			TS_ASSERT_EQUALS(map1.size(), 0);
		}

};