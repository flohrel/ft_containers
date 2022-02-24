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

		void	testConstructor(void)
		{
			TS_ASSERT_EQUALS(v1.size(), 0);
			TS_ASSERT_EQUALS(v2.size(), 3);
			for (ft::vector<int>::const_iterator it = v2.begin(); it != v2.end(); ++it)
			{
				TS_ASSERT_EQUALS(*it, 42);
			}
			TS_ASSERT_EQUALS(v2, v3);
			TS_ASSERT_EQUALS(v2, v4);
		}

		void	testEmpty(void)
		{
			TS_ASSERT(v1.empty());
		}

		void	testCapacity(void)
		{
			TS_ASSERT_LESS_THAN_EQUALS(v1.size(), v1.capacity());
			TS_ASSERT_LESS_THAN_EQUALS(v2.size(), v2.capacity());
			TS_ASSERT_LESS_THAN_EQUALS(v3.size(), v3.capacity());
			TS_ASSERT_LESS_THAN_EQUALS(v4.size(), v4.capacity());
		}

		void	testMaxsize(void)
		{
			std::allocator<int> alloc;
			TS_ASSERT_EQUALS(v2.max_size(), alloc.max_size());
		}

		void	testReserve(void)
		{
			std::allocator<int> alloc;
			v2.reserve(10);
			TS_ASSERT_LESS_THAN_EQUALS(v2.capacity(), 10);
			TS_ASSERT_EQUALS(v2.size(), 3);
			TS_ASSERT_THROWS(v3.reserve(alloc.max_size() + 1), std::length_error);
		}

		void	testClear(void)
		{
			v4.clear();
			TS_ASSERT_EQUALS(v4.size(), 0);
		}

		void	testAt(void)
		{
			TS_ASSERT_EQUALS(v2[0], 42);
			TS_ASSERT_EQUALS(v2.at(2), 42);
			TS_ASSERT_THROWS(v2.at(9), std::out_of_range);
		}

		void	testInsert1(void)
		{
			ft::vector<int>::iterator it = v2.begin();
			it++;
			TS_ASSERT_EQUALS(v2.insert(it, 21), it);
			TS_ASSERT_EQUALS(v2[1], 21);
			TS_ASSERT_EQUALS(v2[2], 42);
			TS_ASSERT_EQUALS(v2[3], 42);
			TS_ASSERT_EQUALS(v2.size(), 4);
		}

		// void	testInsert2(void)
		// {

		// }

};