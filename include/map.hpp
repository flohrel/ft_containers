#ifndef __MAP__H__
# define __MAP__H__

# include "utility.hpp"
# include "rb_tree.hpp"
# include "reverse_iterator.hpp"
# include "algorithm.hpp"

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
				friend class map;

				protected:
					key_compare comp;

					value_compare(Compare c)
						: comp(c)
					{ }

				public:

					~value_compare()
					{ }

					bool
					operator()(const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }

			};

			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp), _bst()
			{ }

			template<class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
				: _alloc(alloc), _comp(comp), _bst()
			{
				insert(first, last);
			}

			map(const map& other)
				: _alloc(other._alloc), _comp(other._comp), _bst()
			{
				insert(other.begin(), other.end());
			}

			~map()
			{ }

			map&
			operator=(const map& rhs)
			{
				_bst = rhs._bst;
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

			void
			clear()
			{ _bst.clear(); }

			ft::pair<iterator, bool>
			insert(const value_type& value)
			{
				return (_bst.insert(value));
			}

			iterator
			insert(iterator hint, const value_type& value)
			{
				(void)hint;
				return (_bst.insert(value).first);
			}

			template<class InputIt>
			void
			insert(InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
			{
				for (; first != last; first++)
				{
					insert(*first);
				}
			}

			void
			erase(iterator pos)
			{
				if (pos == end())
				{
					return ;
				}
				if (find(pos->first) != end())
				{
					_bst.erase(pos.base());
				}
			}

			void
			erase(iterator first, iterator last)
			{
				iterator	tmp = first;

				if (tmp == end() || (find(tmp->first) == end()))
				{
					return ;
				}
				while (tmp != end())
				{
					if (tmp == last)
					{
						while (first != last)
						{
							tmp = first++;
							erase(tmp);
						}
						break ;
					}
					tmp++;
				}
			}

			size_type
			erase( const Key& key )
			{
				iterator	pos;

				pos = find(key);
				if (pos != end())
				{
					_bst.erase(pos.base());
					return (1);
				}
				return (0);
			}

			void
			swap(map& other)
			{
				std::swap(_alloc, other._alloc);
				std::swap(_comp, other._comp);
				_bst.swap(other._bst);
			}


		/* 
		**	MODIFIERS
		*/
			size_type
			count(const Key& key) const
			{ return (_bst.find(key) != end()); }

			iterator
			find( const Key& key )
			{ return (_bst.find(key)); }

			const_iterator
			find( const Key& key ) const
			{ return (const_iterator(_bst.find(key))); }

			ft::pair<iterator,iterator>
			equal_range(const Key& key)
			{ return (ft::make_pair<iterator,iterator>(lower_bound(key), upper_bound(key))); }
	
			ft::pair<const_iterator,const_iterator>
			equal_range(const Key& key) const
			{ return (ft::make_pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key))); }

			iterator
			lower_bound(const Key& key)
			{ return (_bst.lower_bound(key)); }

			const_iterator
			lower_bound(const Key& key) const
			{ return (const_iterator(_bst.lower_bound(key))); }

			iterator
			upper_bound(const Key& key)
			{ return (_bst.upper_bound(key)); }

			const_iterator
			upper_bound(const Key& key) const
			{ return (_bst.upper_bound(key)); }

			key_compare
			key_comp() const
			{ return (_comp); }
	
			value_compare
			value_comp() const
			{ return (value_compare(_comp)); }

			void
			print_tree()
			{ _bst.print_tree(); }
			
		private:
			allocator_type						_alloc;
			key_compare							_comp;
			rb_tree<value_type, Key, Compare>	_bst;

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
		{
			return (false);
		}

		typename map<Key,T,Compare,Alloc>::value_compare comp = lhs.value_comp();

		for (typename map<Key,T,Compare,Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin(); lit != lhs.end(); lit++, rit++)
		{
			if (comp(*lit, *rit) || comp(*rit, *lit))
			{
				return (false);
			}
		}
		return (true);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool
	operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(lhs == rhs)); }

	template< class Key, class T, class Compare, class Alloc >
	bool
	operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class Key, class T, class Compare, class Alloc >
	bool
	operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(rhs < lhs)); }

	template< class Key, class T, class Compare, class Alloc >
	bool
	operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return (rhs < lhs); }
	
	template< class Key, class T, class Compare, class Alloc >
	bool
	operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(lhs < rhs)); }

	template< class Key, class T, class Compare, class Alloc >
	void
	swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
	{ lhs.swap(rhs); }

}

#endif