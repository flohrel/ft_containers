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

		public:
			/**
			 * @brief default constructor
			 */
			explicit vector(const alloc_type& alloc = alloc_type())
			: _alloc(alloc), _start(), _finish(), _end_of_storage()
			{ }

			/**
			 * @brief fill constructor
			 */
			explicit vector(size_type n, const value_type& val = value_type(), const alloc_type& alloc = alloc_type())
				: _alloc(alloc)
			{
				_start = _alloc.allocate(n);
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
				_start = _alloc.allocate(distance(first, last));
				while (first != last)
				{
					_alloc.construct(_finish++, *first++);
				}
				_end_of_storage = _finish;
			}

			/**
			 * @brief copy constructor
			 */
			vector(const vector& x)
				: _alloc(x._alloc)
			{
				_start = _alloc.allocate(x.size());
				_finish = _start;
				for (iterator it = x.begin(); it != x.end(); it++)
				{
					*_finish++ = *it;
				}
				_end_of_storage = _finish;
			}

			/**
			 * @brief destructor
			 */
			~vector()
			{
				pointer	tmp;

				tmp = _start;
				while (tmp != _finish)
				{
					_alloc.destroy(tmp);
				}
				_alloc.deallocate(_start, capacity());
			}

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

			size_type
			size() const
			{ return (size_type(_finish - _start)); }

			size_type
			max_size() const
			{ return (_alloc.max_size()); }

			size_type
			capacity() const
			{ return (size_type(_end_of_storage - _start)); }

			alloc_type
			get_allocator() const
			{ return (alloc_type(_alloc)); }
	};
}

#endif