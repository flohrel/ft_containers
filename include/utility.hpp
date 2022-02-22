#ifndef __UTILITY__H__
#define __UTILITY__H__

#include <string>

namespace ft
{
	template<typename T>
	std::string
	to_string(T n)
	{
		std::ostringstream	os;

		os << n;
		return (os.str());
	}
}

#endif