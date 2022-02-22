#ifndef __VECTOR__H__
# define __VECTOR__H__

# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "utility.hpp"

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
				_finish = _start;
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
				for (const_iterator it = x.begin(); it != x.end(); it++)
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
				clear();
				_alloc.deallocate(_start, capacity());
			}
			
			// vector&
			// operator=(const vector& other)
			// {
				
			// }

			alloc_type
			get_allocator() const
			{ return (alloc_type(_alloc)); }


		/* 
		**	ITERATORS
		*/

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

		/* 
		**	CAPACITY
		*/

			size_type
			size() const
			{ return (size_type(_finish - _start)); }

			size_type
			max_size() const
			{ return (_alloc.max_size()); }

			// void
			// resize(size_type n, value_type val = value_type())
			// {
			// 	if (n < size())
				

			// }

			void
			reserve(size_type n)
			{
				if (n > max_size())
					throw (std::length_error("vector::reserve"));

				size_t	old_capacity = capacity();

				if (n > old_capacity)
				{
					pointer	new_start = _alloc.allocate(n);
					pointer new_finish = new_start;

					for (pointer p = _start; p != _finish; p++)
					{
						_alloc.construct(new_finish++, *p);
						_alloc.destroy(p);
					}
					_alloc.deallocate(_start, old_capacity);
					_start = new_start;
					_finish = new_finish;
					_end_of_storage = _start + n;
				}
			}

			size_type
			capacity() const
			{ return (size_type(_end_of_storage - _start)); }

			void
			clear()
			{
				while (_finish != _start)
				{
					_alloc.destroy(--_finish);
				}
			}

			bool
			empty() const
			{ return (size() == 0); }

		/* 
		**	ELEMENT ACCESS
		*/

			reference
			operator[](size_type pos)
			{
				return (*(_start + pos));
			}

			const_reference
			operator[](size_type pos) const
			{
				return (*(_start + pos));
			}

			reference
			at(size_type n)
			{
				_range_check(n, size());
				return ((*this)[n]);
			}

			const_reference
			at(size_type n) const
			{
				_range_check(n, size());
				return ((*this)[n]);
			}

			reference
			front()
			{ return (*(_start)); }

			const_reference
			front() const
			{ return (*(_start)); }

			reference
			back()
			{ return (*(_finish - 1)); }

			const_reference
			back() const
			{ return (*(_finish - 1)); }

		private:
			void
			_range_check(size_type n, size_type size)
			{
				if (n >= size)
					throw (std::out_of_range("vector::_range_check: n (which is " + ft::to_string(n)
											+ ") >= this->size() (which is " + ft::to_string(size) + ")"));
			}


	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);

		typename ft::vector<T>::const_iterator	first1 = lhs.begin();
		typename ft::vector<T>::const_iterator	first2 = rhs.begin();
		typename ft::vector<T>::const_iterator	last1 = lhs.end();

		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (rhs < lhs); }

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs < rhs)); }

}

#endif