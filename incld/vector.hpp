#ifndef __VECTOR__H__
# define __VECTOR__H__

# include <memory>
# include "iterator.hpp"
# include "type_traits.hpp"

namespace ft
{
	template < typename T, typename Allocator = std::allocator< T > >
	class vector
	{
		public:
			typedef T									value_type;
			typedef Allocator 							allocator_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
		
		private:
			allocator_type	_allocator;
			pointer			_start;
			pointer			_end;
			size_type		_size;
			size_type		_capacity;

		public:
			/**
			 * @brief default constructor
			 */
			explicit vector( const allocator_type& alloc = allocator_type() )
				: _allocator(alloc), _size(0), _capacity(0)
			{ 
				_start = _allocator.allocate(_capacity);
				_end = _start;
			}

			/**
			 * @brief fill constructor
			 */
			explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() )
				: _allocator(alloc), _size(n), _capacity(n)
			{
				_start = _allocator.allocate(_capacity);
				_end = _start;
				while (n--)
				{
					_allocator.construct(_end++, val);
				}
			}

			/**
			 * @brief range constructor
			 * uses enable_if to avoid it being used when we need a fill constructor
			 */
			template <class InputIterator>
			vector( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = NULL )
				: _allocator(alloc)
			{
				_capacity = distance(first, last);
				_size = _capacity;
				_start = _allocator.allocate(_capacity);
				while (first != last)
				{
					_allocator.construct(_end++, *first);
				}
			}

			/**
			 * @brief copy constructor
			 */
			vector( const vector& x )
				: _allocator(x._allocator), _size(x._size), _capacity(x._capacity)
			{
				
			}
			~vector( void ) { delete (_start);}

	};
}

#endif