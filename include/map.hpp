#ifndef __MAP__H__
#define __MAP__H__

#include "utility.hpp"
#include "rb_tree.hpp"
#include "reverse_iterator.hpp"
#include <map>								// TO DELETE

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef Key																			key_type;
			typedef T																			mapped_type;
			typedef pair<const key_type, mapped_type>											value_type;
			typedef Compare																		key_compare;
			typedef Allocator 																	allocator_type;
			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t																difference_type;
			typedef typename Allocator::pointer													pointer;
			typedef typename Allocator::const_pointer											const_pointer;
			typedef typename Allocator::reference												reference;
			typedef typename Allocator::const_reference											const_reference;
			typedef typename ft::rb_tree<value_type, key_type, Compare>::iterator				iterator;
			typedef typename ft::rb_tree<value_type, key_type, Compare>::const_iterator			const_iterator;
			typedef typename ft::rb_tree<value_type, key_type, Compare>::reverse_iterator		reverse_iterator;
			typedef typename ft::rb_tree<value_type, key_type, Compare>::const_reverse_iterator	const_reverse_iterator;

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

			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp), _bst()
			{ }

			// template<class InputIt>
			// map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			// { }

			// map(const map& other)
			// { }

			~map()
			{ clear(); }

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
		**	ELEMENT ACCESS
		*/
			mapped_type&
			at(const Key& key)
			{
				iterator it = find(key);

				if (it == end())
				{
        			throw (std::out_of_range("map::at - index out of range"));
				}
				return (it->second);
			}

			const mapped_type&
			at(const Key& key) const
			{
				const_iterator it = find(key);

				if (it == end())
				{
        			throw (std::out_of_range("map::at - index out of range"));
				}
				return (it->second);
			}

			mapped_type&
			operator[](const Key& key)
			{ return (_bst.insert(ft::make_pair(key, mapped_type())).first->second); }

		/* 
		**	ITERATORS
		*/
			iterator
			begin()
			{ return (_bst.begin()); }

			const_iterator
			begin() const
			{ return (_bst.begin()); }

			iterator
			end()
			{ return (_bst.end()); }

			const_iterator
			end() const
			{ return (_bst.end()); }

			reverse_iterator
			rbegin()
			{ return (_bst.rbegin()); }

			const_reverse_iterator
			rbegin() const
			{ return (_bst.rbegin()); }

			reverse_iterator
			rend()
			{ return (_bst.rend()); }

			const_reverse_iterator
			rend() const
			{ return (_bst.rend()); }

		/* 
		**	CAPACITY
		*/
			bool
			empty() const
			{ return (_bst.size() == 0); }

			size_type
			max_size() const
			{ return (_bst.max_size()); }

			size_t
			size() const
			{ return (_bst.size()); }

		/* 
		**	MODIFIERS
		*/
			ft::pair<iterator, bool>
			insert(const value_type& value)
			{
				return (_bst.insert(value));
			}

			iterator
			insert(iterator hint, const value_type& value)
			{
				return (_bst.insert(value).first);
			}

			template<class InputIt>
			void
			insert(InputIt first, InputIt last)
			{
				for (; first != last; first++)
				{
					insert(*first);
				}
			}

			void
			erase(iterator pos)
			{ _bst.erase(pos.base()); }

			void
			clear()
			{ _bst.clear(); }

			iterator
			find( const Key& key )
			{ return (_bst.find(key)); }

			const_iterator
			find( const Key& key ) const
			{ return (_bst.find(key)); }

			void
			print_tree()
			{ _bst.print_tree(); }
			
		private:
			Allocator							_alloc;
			Compare								_comp;
			rb_tree<value_type, Key, Compare>	_bst;

	};
}

#endif