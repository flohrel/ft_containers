#ifndef __UTILITY__H__
#define __UTILITY__H__

#include <sstream>
#include <utility>

namespace ft
{
	template<typename Pair>
    struct select_first
    {
		typename Pair::first_type&
		operator()(Pair& x) const
		{ return (x.first); }

		const typename Pair::first_type&
		operator()(const Pair& x) const
		{ return (x.first); }

	};

	template<typename T>
    struct identity
    {
      T&
      operator()(T& x) const
      { return (x); }

      const T&
      operator()(const T& x) const
      { return (x); }

    };

	template <typename T1, typename T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			pair()
				: first(), second()
			{ }

			template<class U, class V>
			pair(const pair<U, V>& pr)
				: first(pr.first), second(pr.second)
			{ }

			pair(const first_type& a, const second_type& b)
				: first(a), second(b)
			{ }

			pair&
			operator=(const pair& rhs)
			{
				if (this != &rhs)
				{
					first = rhs.first;
					second = rhs.second;
				}
				return (*this);
			}

	};

	template <class T1, class T2>
	bool
	operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ((lhs.first == rhs.first) && (lhs.second == rhs.second)); }

	template <class T1, class T2>
	bool
	operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T1, class T2>
	bool
	operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && (lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool
	operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool
	operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (rhs < lhs); }

	template <class T1, class T2>
	bool
	operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs < rhs)); }

	template <class T1,class T2>
	pair<T1,T2>
	make_pair(T1 x, T2 y)
	{
    	return (pair<T1,T2>(x,y));
	}

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