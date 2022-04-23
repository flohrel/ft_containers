#ifndef __VECTOR__H__
# define __VECTOR__H__

# include <algorithm>
# include <memory>
# include <stdexcept>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
#include <iostream>

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
			{
				_start = _alloc.allocate(0);
				_end_of_storage = _start;
				_finish = _start;
			}

			/**
			 * @brief fill constructor
			 */
			explicit vector(size_type n, const value_type& val = value_type(), const alloc_type& alloc = alloc_type())
				: _alloc(alloc)
			{
				size_t	len = _check_init_length(n);

				_start = _alloc.allocate(len);
				_end_of_storage = _start + len;
				_finish = _start + n;
				_uninitialised_fill(_start, _finish, val);
			}

			/**
			 * @brief range constructor
			 * uses enable_if to avoid using it when we need a fill constructor
			 */
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const alloc_type& alloc = alloc_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
				: _alloc(alloc)
			{
				size_t	len = _check_init_length(ft::distance(first, last));

				_start = _alloc.allocate(len);
				_end_of_storage = _start + len;
				_finish = _uninitialised_copy(first, last, _start);

			}

			/**
			 * @brief copy constructor
			 */
			vector(const vector& x)
				: _alloc(x._alloc)
			{
				size_t	len = _check_init_length(x.size());

				_start = _alloc.allocate(len);
				_end_of_storage = _start + len;
				_finish = _uninitialised_copy(x.begin(), x.end(), _start);
			}

			/**
			 * @brief destructor
			 */
			~vector()
			{
				clear();
				_alloc.deallocate(_start, capacity());
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
				if (n < size())
				{
					_erase_at_end(_start + n);
				}
				else
				{
					reserve(n);
					n -= size();
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
				if (n >= capacity())
				{
					size_t	len = _check_length(n, "vector::reserve");
					pointer	new_start = _alloc.allocate(len);
					pointer new_finish = new_start;

					for (pointer p = _start; p != _finish; p++, new_finish++)
					{
						_alloc.construct(new_finish, *p);
						_alloc.destroy(p);
					}
					_alloc.deallocate(_start, capacity());
					_start = new_start;
					_finish = new_finish;
					_end_of_storage = _start + len;
				}
			}

			size_type
			capacity() const
			{ return (_end_of_storage - _start); }

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

			T*
			data()
			{ return (_start); }

			const T*
			data() const
			{ return (_start); }

		/* 
		**	MODIFIERS
		*/
			template <class InputIterator>
			void
			assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_type	n = ft::distance(first, last);

				if (n < size())
				{
					_erase_at_end(_copy(first, last, _start));
				}
				else
				{
					if (n > capacity())
					{
						int len = _check_length(n, "vector::assign");
						_destroy(_start, _finish);
						_alloc.deallocate(_start, capacity());
						_start = _alloc.allocate(len);
						_end_of_storage = _start + len;
					}
					_finish = _start + n;
				}
				_uninitialised_copy(first, last, _start);
			}

			void
			assign(size_type n, const value_type& val)
			{
				if (n < size())
				{
					_erase_at_end(_start + n);
				}
				else
				{
					if (n > capacity())
					{
						_destroy(_start, _finish);
						_alloc.deallocate(_start, capacity());
						int len = _check_length(n, "vector::assign");
						_start = _alloc.allocate(len);
						_end_of_storage = _start + len;
					}
					_finish = _start + n;
				}
				_uninitialised_fill(_start, _finish, val);
			}

			void
			clear()
			{
				while (_finish != _start)
				{
					--_finish;
					_alloc.destroy(_finish);
				}
			}

			iterator
			erase(iterator pos)
			{
				if ((pos + 1) != end())
				{
					for (iterator it = pos + 1; it != end(); it++)
					{
						*(it - 1) = *it;
					}
				}
				--_finish;
				_alloc.destroy(_finish);
				return (pos);
			}

			iterator 
			erase(iterator first, iterator last)
			{
				iterator dest = first;

				if (last != end())
				{
					for (; last != end(); dest++, last++)
					{
						(*dest) = (*last);
					}
				}
				_erase_at_end(dest.base());
				return (first);
			}

			iterator
			insert(iterator position, const value_type& val)
			{
				size_t	new_size = size() + 1;

				if (new_size > capacity())
				{
					size_t len = _check_length(new_size, "vector::insert");
					pointer	new_start = _alloc.allocate(len);
					pointer ptr = _uninitialised_copy(begin(), position, new_start);
					_alloc.construct(ptr, val);
					pointer new_finish = _uninitialised_copy(position, iterator(_finish), ptr + 1);
					_destroy(_start, _finish);
					_alloc.deallocate(_start, capacity());
					_start = new_start;
					_finish = new_finish;
					_end_of_storage = _start + len;
					return (iterator(ptr));
				}
				else
				{
					if (position != end())
					{
						_alloc.construct(_finish, value_type());
						_backward_copy(iterator(_finish - 1), position, iterator(_finish));
						(*position) = val;
					}
					else
					{
						_alloc.construct(_finish, val);
					}
					_finish++;
					return (position);
				}
			}

			void
			insert(iterator position, size_type n, const value_type& val)
			{
				if (n != 0)
				{
					size_t	new_size = size() + n;

					if (new_size > capacity())
					{
						size_t	len = _check_length(new_size, "vector::insert");
						pointer	new_start = _alloc.allocate(len);
						pointer	new_finish = _uninitialised_copy(iterator(_start), position, new_start);
						new_finish = _uninitialised_fill(new_finish, new_finish + n, val);
						new_finish = _uninitialised_copy(position, iterator(_finish), new_finish);
						_destroy(_start, _finish);
						_alloc.deallocate(_start, capacity());
						_start = new_start;
						_finish = new_finish;
						_end_of_storage = _start + len;
					}
					else
					{
						const size_type	elems_after = end() - position;
						pointer			old_finish(_finish);
						
						if (elems_after > n)
						{
							_finish = _uninitialised_copy(_finish - n, _finish, _finish);
							_backward_copy(iterator(old_finish - n), position, old_finish);
							_fill(position, position + n, val);
						}
						else
						{
							_finish = _uninitialised_fill(_finish, _finish + (n - elems_after), val);
							_finish = _uninitialised_copy(position, iterator(old_finish), _finish);
							_fill(position, iterator(old_finish), val);
						}
					}
				}
			}

			template <class InputIterator>
    		void
			insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				if (first != last)
				{
					size_t	n = ft::distance(first, last);
					size_t	new_size = size() + n;

					if (new_size > capacity())
					{
						size_t	len = _check_length(new_size, "vector::insert");
						pointer	new_start = _alloc.allocate(len);
						pointer	new_finish = _uninitialised_copy(iterator(_start), position, new_start);
						new_finish = _uninitialised_copy(first, last, new_finish);
						new_finish = _uninitialised_copy(position, iterator(_finish), new_finish);
						_destroy(_start, _finish);
						_alloc.deallocate(_start, capacity());
						_start = new_start;
						_finish = new_finish;
						_end_of_storage = _start + len;
					}
					else
					{
						const size_type	elems_after = end() - position;
						pointer			old_finish(_finish);
						
						if (elems_after > n)
						{
							_finish = _uninitialised_copy(_finish - n, _finish, _finish);
							_backward_copy(iterator(old_finish - n), position, old_finish);
							_copy(first, last, position);
						}
						else
						{
							_uninitialised_copy(first + elems_after, last, _finish);
							_finish += (n - elems_after);
							_finish = _uninitialised_copy(position, iterator(old_finish), _finish);
							_copy(first, first + elems_after, position);
						}
					}
				}
			}

			void
			push_back(const value_type& val)
			{
				resize(size() + 1, val);
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

			void
			swap(vector& x)
			{
				std::swap(_alloc, x._alloc);
				std::swap(_start, x._start);
				std::swap(_finish, x._finish);
				std::swap(_end_of_storage, x._end_of_storage);
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

			size_t
			_check_init_length(size_type n)
			{
				if (n > max_size())
				{
					throw ("cannot create std::vector larger than max_size()");
				}
				return (n);
			}

			size_t
			_check_length(size_type n, const char* error_msg)
			{
				if (n > max_size() - size())
				{
					throw (std::length_error(error_msg));
				}
				size_t len = size() + std::max(size(), n);
				return ((len < size()) || (len > max_size()) ? max_size() : len);
			}

			void
			_erase_at_end(pointer pos)
			{
				_destroy(pos, _finish);
				_finish = pos;
			}

			void
			_destroy(pointer first, pointer last)
			{
				for (; first != last; first++)
				{
					_alloc.destroy(first);
				}
			}

			iterator
			_fill(iterator first, iterator last, const value_type& val)
			{
				for (; first != last; first++)
				{
					(*first) = val;
				}
				return (first);
			}

			pointer
			_uninitialised_fill(pointer first, pointer last, const value_type& val)
			{
				for (; first != last; first++)
				{
					_alloc.construct(first, val);
				}
				return (first);
			}

			template< class InputIt, class OutputIt >
			OutputIt
			_copy(InputIt first, InputIt last, OutputIt d_first)
			{
				for (; first != last; first++, d_first++)
				{
					(*d_first) = (*first);
				}
				return (d_first);
			}

			template< class InputIt, class OutputIt >
			OutputIt
			_backward_copy(InputIt first, InputIt last, OutputIt d_first)
			{
				while (first != last)
				{
					*(--d_first) = *(--first);
				}
				return (d_first);
			}

			template< class InputIt, class OutputIt >
			OutputIt
			_uninitialised_copy(InputIt first, InputIt last, OutputIt d_first)
			{
				for (; first != last; first++, d_first++)
				{
					_alloc.construct(d_first, *first);
				}
				return (d_first);
			}

	};

	template<class T, class Alloc>
	void
	swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{ lhs.swap(rhs); }

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