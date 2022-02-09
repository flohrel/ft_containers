#ifndef __REVERSE_ITERATOR__H__
# define __REVERSE_ITERATOR__H__

# include "iterator_traits.hpp"

	template< typename Iterator >
	struct reverse_iterator : public iterator< typename iterator_traits< Iterator >::iterator_category,
			typename iterator_traits< Iterator >::value_type,
			typename iterator_traits< Iterator >::difference_type,
			typename iterator_traits< Iterator >::pointer,
			typename iterator_traits< Iterator >::reference >
	{
		protected:
			Iterator	_current;

			typedef iterator_traits< Iterator >				traits_type;

		public:
    		typedef Iterator								iterator_type;
    		typedef typename traits_type::difference_type	difference_type;
    		typedef typename traits_type::pointer			pointer;
    		typedef typename traits_type::reference			reference;

			reverse_iterator( void ) : _current() { }
			reverse_iterator( iterator_type x ) : _current(x) { }
			reverse_iterator( const reverse_iterator& x ) : _current(x._current) { }

			iterator_type		base( void ) const { return (_current); }
			
			reference			operator*( void ) const { Iterator tmp = _current; return (*--tmp); }
			pointer				operator->( void ) const { return (std::addressof(operator*())); }

			reverse_iterator&	operator++( void ) { --_current; return (*this); }
			reverse_iterator	operator++( int ) { reverse_iterator tmp = *this; --_current; return (tmp); }
			reverse_iterator&	operator--( void ) { ++_current; return (*this); }
			reverse_iterator	operator--( int ) { reverse_iterator tmp = *this; ++_current; return (tmp); }
			reverse_iterator	operator+( difference_type n ) const { return (reverse_iterator(_current - n)); }
			reverse_iterator&	operator+=( difference_type n ) { _current -= n; return (*this); }
			reverse_iterator	operator-( difference_type n ) const { return (reverse_iterator(_current + n)); }
			reverse_iterator&	operator-=( difference_type n ) { _current += n; return (*this); }
			reference			operator[]( difference_type n ) const { return (*(*this + n)); }

			template< typename IteratorL, typename IteratorR >
			bool	operator==( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y )
			{ return (x.base() == y.base()); }

			template< typename IteratorL, typename IteratorR >
			bool	operator<( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y )
			{ return (x.base() < y.base()); }

			template< typename IteratorL, typename IteratorR >
			bool	operator!=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y )
			{ return !(x == y); }

			template< typename IteratorL, typename IteratorR >
			bool	operator>( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y )
			{ return (y < x); }

			template< typename IteratorL, typename IteratorR >
			bool	operator<=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y )
			{ return !(y < x); }

			template< typename IteratorL, typename IteratorR >
			bool	operator>=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y )
			{ return !(x < y); }

			template< class Iterator >
			reverse_iterator< Iterator >	operator+( typename reverse_iterator< Iterator >::difference_type n, const reverse_iterator< Iterator >& it )
			{ return (reverse_iterator< Iterator >(it.base() - n)) }

			template< typename IteratorL, typename IteratorR >
			typename reverse_iterator< IteratorL >::difference_type	operator-( const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs )
			{ return (rhs.base() - lhs.base()); }
	};


#endif