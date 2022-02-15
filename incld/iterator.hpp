#ifndef __ITERATOR__H__
#define __ITERATOR__H__

# include "iterator_traits.hpp"

namespace ft
{
	template<typename Iterator>
	struct random_access_iterator : public iterator<random_access_iterator_tag,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference>
	{
		public:
			typedef iterator_traits<Iterator>				traits_type;
    		typedef Iterator								iterator_type;
    		typedef typename traits_type::difference_type	difference_type;
    		typedef typename traits_type::pointer			pointer;
    		typedef typename traits_type::reference			reference;

		protected:
			pointer		_current;

		public:
			random_access_iterator(void)
			: _current()
			{ }

			random_access_iterator(iterator_type x)
			: _current(x)
			{ }

			random_access_iterator(const random_access_iterator& x)
			: _current(x._current)
			{ }

			iterator_type
			base(void) const
			{ return (_current); }
			
			reference
			operator*(void) const
			{ return (*_current); }

			pointer
			operator->(void) const
			{ return (&(operator*())); }

			random_access_iterator&
			operator++(void)
			{
				++_current;
				return (*this);
			}

			random_access_iterator
			operator++(int)
			{
				random_access_iterator tmp = *this;
				++_current;
				return (tmp);
			}

			random_access_iterator&
			operator--(void)
			{
				--_current;
				return (*this);
			}

			random_access_iterator
			operator--(int)
			{
				random_access_iterator tmp = *this;
				--_current;
				return (tmp);
			}

			random_access_iterator
			operator+(difference_type n) const
			{ return (random_access_iterator(_current + n)); }

			random_access_iterator&
			operator+=(difference_type n)
			{
				_current += n;
				return (*this);
			}

			random_access_iterator
			operator-(difference_type n) const
			{ return (random_access_iterator(_current - n)); }

			random_access_iterator&
			operator-=(difference_type n)
			{
				_current -= n;
				return (*this);
			}

			reference
			operator[](difference_type n) const
			{ return (*(*this + n)); }

			operator random_access_iterator< const Iterator >() const
			{ return _current; }

	};

	template<typename IteratorL, typename IteratorR>
	bool	operator==(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<typename IteratorL, typename IteratorR>
	bool	operator<(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template<typename IteratorL, typename IteratorR>
	bool	operator!=(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return !(lhs == rhs); }

	template<typename IteratorL, typename IteratorR>
	bool	operator>(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return (rhs < lhs); }

	template<typename IteratorL, typename IteratorR>
	bool	operator<=(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return !(rhs < lhs); }

	template<typename IteratorL, typename IteratorR>
	bool	operator>=(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return !(lhs < rhs); }

	template<typename Iter>
	random_access_iterator<Iter>
	operator+(typename random_access_iterator< Iter >::difference_type n, const random_access_iterator< Iter >& it)
	{ return (random_access_iterator< Iter >(it.base() + n)); }

	template<typename IteratorL, typename IteratorR>
	typename random_access_iterator< IteratorL >::difference_type
	operator-(const random_access_iterator< IteratorL >& lhs, const random_access_iterator< IteratorR >& rhs)
	{ return (rhs.base() - lhs.base()); }

	/**
	 * @brief ft::distance specialization
	 */
	template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, input_iterator_tag)
    {
		typename iterator_traits< InputIterator >::difference_type	n = 0;

		while (first++ != last)
		{
			++n;
		}
    	return (n);
    }

	/**
	 * @brief ft::distance specialization for random access iterators
	 */
	template<typename RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::difference_type
	_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    { return (last - first); }

	/**
	 * @brief determine the distance between two iterators
	 */
	template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    { return (_distance(first, last, iterator_category(first))); }
}

#endif