#include "cxxtest/TestSuite.h"
#include "map.hpp"

std::map<std::string, int>	test1;
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

		void	testInsert(void)
		{
			ft::pair<ft::map<std::string, int>::iterator, bool> test = map1.insert(ft::make_pair("foo", 42));

			std::cout << test.first->first << std::endl;
		}

		// void	testDummy()
		// {
		// 	test.insert(std::make_pair("foo", 42));
		// 	test.insert(std::make_pair("bar", 0));
		// 	test.insert(std::make_pair("baz", 1337));
		// 	test.insert(std::make_pair("quux", 42));
		// 	test.insert(std::make_pair("quux", 1337));
		// 	std::map<std::string, int>::iterator it = test.end();
		// 	it--;
		// 	std::cout << (*it).first << " - " << (*it).second << std::endl;
		// 	it++;
		// 	std::cout << (*it).first << " - " << (*it).second << std::endl;
		// 	it++;
		// 	std::cout << (*it).first << " - " << (*it).second << std::endl;
		// 	it++;
		// 	it--;
		// 	std::cout << (*it).first << " - " << (*it).second << std::endl;
		// }


};