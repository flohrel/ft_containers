#ifndef __ITERATOR__H__
#define __ITERATOR__H__

# include "iterator_traits.hpp"

namespace ft
{
	template<typename Iterator>
	struct random_access_iterator
	{
		protected:
			typedef iterator_traits<Iterator>					traits_type;

		public:
    		typedef typename traits_type::value_type			value_type;
    		typedef typename traits_type::difference_type		difference_type;
    		typedef typename traits_type::pointer				pointer;
    		typedef typename traits_type::reference				reference;
			typedef std::random_access_iterator_tag				iterator_category;

		protected:
			Iterator	_current;

		public:
			random_access_iterator(void)
				: _current(Iterator())
			{ }

			explicit
			random_access_iterator(const Iterator& it)
				: _current(it)
			{ }

			template<typename Iter>
			random_access_iterator(const random_access_iterator<Iter>& it)
				: _current(it.base())
			{ }

			~random_access_iterator(void)
			{ }

			const Iterator&
			base(void) const
			{ return (_current); }
			
			template<typename Iter>
			random_access_iterator&
			operator=(const random_access_iterator& rhs)
			{
				_current = rhs.base();
				return (*this);
			}

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
	operator+(typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it)
	{ return (it + n); }

	template<typename IteratorL, typename IteratorR>
	typename random_access_iterator<IteratorL>::difference_type
	operator-(const random_access_iterator<IteratorL>& lhs, const random_access_iterator<IteratorR>& rhs)
	{ return (lhs.base() - rhs.base()); }

	/**
	 * @brief ft::distance specialization
	 */
	template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
		typename iterator_traits<InputIterator>::difference_type	n = 0;

		while (first++ != last)
		{
			++n;
		}
    	return (n);
    }

	/**
	 * @brief ft::distance specialization for random access iterators
	 */
	template<typename Iterator>
	typename iterator_traits<Iterator>::difference_type
	_distance(const random_access_iterator<Iterator>& first, const random_access_iterator<Iterator>& last, std::random_access_iterator_tag)
    { return (last.base() - first.base()); }

	/**
	 * @brief determine the distance between two iterators
	 */
	template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    { return (_distance(first, last, iterator_category(first))); }
}

#endif