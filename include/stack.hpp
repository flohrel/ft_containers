#ifndef __STACK__H__
#define __STACK__H__

# include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:

			typedef T										value_type;
			typedef Container								container_type;
			typedef typename Container::value_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

			container_type		c;

			explicit
			stack( const Container& cont = Container() )
				: c(cont)
			{ }

			stack( const stack& other )
				: c(other.c)
			{ }
			
			~stack( void )
			{ }

			bool
			empty() const
			{ return (c.empty()); }

			size_type
			size() const
			{ return (c.size()); }

			value_type&
			top()
			{ return (c.back()); }

			const value_type&
			top() const
			{ return (c.back()); }

			void
			push (const value_type& val)
			{ c.push_back(val); }

			void
			pop()
			{ c.pop_back(); }


	};

	template <class _T, class _Container>
	bool operator==(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
	{ return (lhs.c == rhs.c ); }

	template <class _T, class _Container>
	bool operator!=(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
	{ return (lhs.c != rhs.c ); }

	template <class _T, class _Container>
	bool operator<(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
	{ return (lhs.c < rhs.c ); }

	template <class _T, class _Container>
	bool operator<=(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
	{ return (lhs.c <= rhs.c ); }

	template <class _T, class _Container>
	bool operator>(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
	{ return (lhs.c > rhs.c ); }

	template <class _T, class _Container>
	bool operator>=(const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs)
	{ return (lhs.c >= rhs.c ); }


}

#endif