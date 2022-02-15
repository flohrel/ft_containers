#ifndef __VECTOR__H__
# define __VECTOR__H__

# include <memory>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "type_traits.hpp"

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Allocator 									alloc_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef ft::random_access_iterator<pointer>			iterator;
			typedef ft::random_access_iterator<const_pointer>	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		private:
			alloc_type		_alloc;
			pointer			_start;
			pointer			_finish;
			pointer			_end_of_storage;
			size_type		_size;
			size_type		_capacity;

		public:
			/**
			 * @brief default constructor
			 */
			explicit vector(const alloc_type& alloc = alloc_type())
			: _alloc(alloc), _size(0), _capacity(0), _start(), _finish(), _end_of_storage()
			{ }

			/**
			 * @brief fill constructor
			 */
			explicit vector(size_type n, const value_type& val = value_type(), const alloc_type& alloc = alloc_type())
				: _alloc(alloc), _size(n), _capacity(n)
			{
				_start = _alloc.allocate(_capacity);
				_finish = _start;
				while (n--)
				{
					_alloc.construct(_finish++, val);
				}
				_end_of_storage = _finish;
			}

			/**
			 * @brief range constructor
			 * uses enable_if to avoid it being used when we need a fill constructor
			 */
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const alloc_type& alloc = alloc_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
				: _alloc(alloc)
			{
				_capacity = distance(first, last);
				_size = _capacity;
				_start = _alloc.allocate(_capacity);
				while (first != last)
				{
					_alloc.construct(_finish++, *first++);
				}
				_end_of_storage = _finish;
			}

			/**
TODO		 * @brief copy constructor
			 */
			vector(const vector& x)
				: _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
			}

			/**
TODO		 * @brief destructor
			 */
			~vector() { delete (_start); }

			iterator
			begin()
			{ return (iterator(_start)); }

			const_iterator
			begin() const
			{ return (const_iterator(_start)); }

			iterator
			end()
			{ return (iterator(_finish)); }

			const_iterator
			end() const
			{ return (const_iterator(_finish)); }

			reverse_iterator
			rbegin()
			{ return (reverse_iterator(end())); }

			const_reverse_iterator
			rbegin() const
			{ return (const_reverse_iterator(end())); }

			reverse_iterator
			rend()
			{ return (reverse_iterator(begin())); }

			const_iterator
			rend() const
			{ return (const_reverse_iterator(begin())); }

	};
}

#endif