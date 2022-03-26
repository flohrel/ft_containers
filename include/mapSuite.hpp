#include "cxxtest/TestSuite.h"
#include "map.hpp"

std::map<std::string, int>	test;
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
			ft::pair<ft::map<std::string, int>::iterator, bool> test1 = map1.insert(ft::make_pair("foo", 42));
			ft::pair<ft::map<std::string, int>::iterator, bool> test2 = map1.insert(ft::make_pair("foo", 42));
			map1.insert(ft::make_pair("bar", 1337));
			map1.insert(ft::make_pair("baz", 13));
			map1.insert(ft::make_pair("quux", 21));
			map1.insert(ft::make_pair("buidi", 42));
			map1.insert(ft::make_pair("test", 42));
			map1.insert(ft::make_pair("zest", 42));
			map1.insert(ft::make_pair("zzz", 42));
			map1.insert(test2.first, ft::make_pair("nouille", 42));
			std::cout << std::endl;
			map2.insert(map1.begin(), map1.end());
			map2.print_tree();
			std::cout << std::endl;
			map1.print_tree();
			std::cout << std::endl;
			map2.clear();
			std::cout << std::endl;
			map2.print_tree();

		}

		void	testIterator(void)
		{
			ft::map<std::string, int>::iterator it = map1.begin();
			ft::map<std::string, int>::iterator it2 = map1.end();

			std::cout << it->first << std::endl;
			std::cout << it2->first << std::endl;
			++it;
			std::cout << it->first << std::endl;
			++it2;
			++it2;
			std::cout << it2->first << std::endl;
			--it2;
			std::cout << it2->first << std::endl;
			--it2;
			std::cout << it2->first << std::endl;
			--it2;
			std::cout << it2->first << std::endl;
			--it2;
			std::cout << it2->first << std::endl;
			--it2;
			std::cout << it2->first << std::endl;

		}

		void	testFind()
		{
			ft::map<std::string, int>::iterator it = map1.find("buidi");

			std::cout << (*it).first << "/" << (*it).second << std::endl;
		}

		void	testAt()
		{
			std::cout << map1.at("quux") << std::endl;
			map1["quux"] = 666;
			std::cout << map1["quux"] << std::endl;
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