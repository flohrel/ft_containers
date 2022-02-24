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
			size_type		_capacity;


		public:

			/**
			 * @brief default constructor
			 */
			explicit vector(const alloc_type& alloc = alloc_type())
			: _alloc(alloc), _start(), _finish(), _capacity(2)
			{ }

			/**
			 * @brief fill constructor
			 */
			explicit vector(size_type n, const value_type& val = value_type(), const alloc_type& alloc = alloc_type())
				: _alloc(alloc), _capacity(2)
			{
				_compute_capacity(n);
				_start = _alloc.allocate(_capacity);
				_finish = _start;
				for (; n > 0; n--, _finish++)
				{
					_alloc.construct(_finish, val);
				}
			}

			/**
			 * @brief range constructor
			 * uses enable_if to avoid using it when we need a fill constructor
			 */
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const alloc_type& alloc = alloc_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
				: _alloc(alloc), _capacity(2)
			{
				_compute_capacity(distance(first, last));
				_start = _alloc.allocate(_capacity);
				_finish = _start;
				for (; first != last; first++, _finish++)
				{
					_alloc.construct(_finish, *first);
				}
			}

			/**
			 * @brief copy constructor
			 */
			vector(const vector& x)
				: _alloc(x._alloc), _capacity(2)
			{
				_compute_capacity(x.size());
				_start = _alloc.allocate(_capacity);
				_finish = _start;
				for (const_iterator it = x.begin(); it != x.end(); it++, _finish++)
				{
					*_finish = *it;
				}
			}

			/**
			 * @brief destructor
			 */
			~vector()
			{
				clear();
				_alloc.deallocate(_start, _capacity);
			}
			
			vector&
			operator=(const vector& rhs)
			{
				if (this != &rhs)
				{
					assign(rhs.begin(), rhs.end());
				}
				return (*this);
			}

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

			void
			resize(size_type n, value_type val = value_type())
			{
				pointer	ptr;

				if (n < size())
				{
					ptr = _start + n;
					while (ptr != _finish)
					{
						_alloc.destroy(ptr);
						++ptr;
					}
					_finish = _start + n;
				}
				else
				{
					if (n > _capacity)
					{
						reserve(n);
					}
					_finish = _start + n;
					while (n--)
					{
						_alloc.construct(_finish, val);
						++_finish;
					}
				}
			}

			void
			reserve(size_type n)
			{
				size_type	old_capacity = _capacity;

				if (n > old_capacity)
				{
					_compute_capacity(n);
					pointer	new_start = _alloc.allocate(n);
					pointer new_finish = new_start;

					for (pointer p = _start; p != _finish; p++, new_finish++)
					{
						_alloc.construct(new_finish, *p);
						_alloc.destroy(p);
					}
					_alloc.deallocate(_start, old_capacity);
					_start = new_start;
					_finish = new_finish;
				}
			}

			size_type
			capacity() const
			{ return (_capacity); }

			bool
			empty() const
			{ return (size() == 0); }

		/* 
		**	ELEMENT ACCESS
		*/

			reference
			operator[](size_type pos)
			{ return (*(_start + pos)); }

			const_reference
			operator[](size_type pos) const
			{ return (*(_start + pos)); }

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

		/* 
		**	MODIFIERS
		*/

			template <class InputIterator>
			void
			assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_type	size = distance(first, last);

				if (size > _capacity)
				{
					reserve(size);
				}

				pointer	ptr = _start;

				for (; first != last; first++, ptr++)
				{
					_alloc.destroy(ptr);
					_alloc.construct(ptr, *first);
				}
			}

			void
			assign(size_type n, const value_type& val)
			{
				if (n > _capacity)
				{
					reserve(n);
				}

				pointer	ptr = _start;

				for (; ptr != _finish; ptr++)
				{
					_alloc.destroy(ptr);
					_alloc.construct(ptr, val);
				}
			}

			void
			clear()
			{
				while (_finish != _start)
				{
					_alloc.destroy(_finish);
					--_finish;
				}
			}

			iterator
			erase(iterator pos)
			{
				iterator	last = end();

				_finish = &(*pos);
				for (; pos != last; pos++)
				{
					_alloc.destroy(&(*pos));
				}
				return (end());
			}

			iterator 
			erase(iterator first, iterator last)
			{
				if (first == last)
				{
					return (last);
				}
				_finish = &(*first);
				for (; first != last; first++)
				{
					_alloc.destroy(&(*first));
				}
				return (end());
			}

			iterator
			insert(iterator position, const value_type& val)
			{
				if (size() == _capacity)
				{
					reserve(size() + 1);
				}

				++_finish;
				for (iterator it = end(); it > position; )
				{
					--it;
					*(it + 1) = *it;
				}
				*position = val;
				return (position);
			}

			// void
			// insert(iterator position, size_type n, const value_type& val)
			// {
			// 	size_type	new_size = size() + n;

			// 	if (capacity() < new_size)
			// 	{
			// 		reserve(new_size);
			// 	}
			// }

			// template <class InputIterator>
    		// void
			// insert(iterator position, InputIterator first, InputIterator last,
			// 		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			// {}

			void
			push_back(const value_type& val)
			{
				if (size() == _capacity)
				{
					reserve(size() + 1);
				}
				_alloc.construct(_finish, val);
				++_finish;
			}

			void
			pop_back()
			{
				if (!empty())
				{
					--_finish;
					_alloc.destroy(_finish);
				}
			}


		private:

			void
			_range_check(size_type n, size_type size) const
			{
				if (n >= size)
				{
					throw (std::out_of_range("vector::_range_check: n (which is " + ft::to_string(n)
											+ ") >= this->size() (which is " + ft::to_string(size) + ")"));
				}
			}

			void
			_compute_capacity(size_type n)
			{
				if (n > max_size())
				{
					throw (std::length_error("vector::reserve"));
				}
				else if (n > (max_size() / 2))
				{
					_capacity = max_size();
				}
				else
				{
					while (_capacity < n)
					{
						_capacity *= 2;
					}
				}
			}

	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return (false);
		}

		typename ft::vector<T>::const_iterator	first1 = lhs.begin();
		typename ft::vector<T>::const_iterator	first2 = rhs.begin();
		typename ft::vector<T>::const_iterator	last1 = lhs.end();

		for (; first1 != last1; first1++, first2++)
		{
			if (!(*first1 == *first2))
			{
				return (false);
			}
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