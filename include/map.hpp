#ifndef __MAP__H__
#define __MAP__H__

#include "utility.hpp"
#include "rb_tree.hpp"
#include "reverse_iterator.hpp"
#include <map>
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef Compare										key_compare;
			typedef Allocator 									allocator_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			// typedef ft::rb_tree_iterator<pointer>			iterator;
			// typedef ft::rb_tree_iterator<const_pointer>		const_iterator;
			// typedef ft::reverse_iterator<iterator>			reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			class value_compare
			{
				friend class map<Key, T, Compare, Allocator>;

				protected:
					Compare comp;

					value_compare()
						: comp(Compare())
					{ }

				public:
					value_compare(Compare c)
						: comp(c)
					{ }

					~value_compare()
					{ }

					bool
					operator()(const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }

			};

		private:
			allocator_type					_alloc;
			Compare							_comp;
			rb_tree<value_type, Compare>	_bst;

		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _comp(comp), _bst()
			{ }

			~map()
			{ }

			map&
			operator=(const map& rhs)
			{
				if (this != &rhs)
				{
					_alloc = rhs._alloc;
					_comp = rhs._comp;
					_bst = rhs._bst;
				}
				return (*this);
			}

			allocator_type
			get_allocator() const
			{ return (allocator_type(_alloc)); }

		/* 
		**	CAPACITY
		*/

			bool
			empty() const
			{ return (_bst.size() == 0); }

			size_type
			max_size() const
			{ return(_alloc.max_size()); }

			size_t
			size() const
			{ return (_bst.size()); }

		/* 
		**	MODIFIERS
		*/
			

	};
}

#endif