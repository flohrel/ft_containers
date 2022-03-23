#ifndef __RB_TREE__H__
#define __RB_TREE__H__

# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "utility.hpp"
#pragma clang diagnostic ignored "-Wunused-parameter"


namespace ft
{
	enum	rb_tree_color
	{
		RED,
		BLACK
	};

	struct rb_tree_node_base
	{
		typedef rb_tree_node_base*	base_ptr;

		rb_tree_color	color;
		base_ptr		parent;
		base_ptr		left;
		base_ptr		right;

		rb_tree_node_base()
			: color(RED), parent(NULL), left(NULL), right(NULL)
		{ }

		rb_tree_node_base(base_ptr p, base_ptr l, base_ptr r, rb_tree_color c = RED)
			: color(c), parent(p), left(l), right(r) 
		{ }

		rb_tree_node_base(const rb_tree_node_base& node)
		{
			color = node.color;
			parent = node.parent;
			left = node.left;
			right = node.right;
		}

		~rb_tree_node_base()
		{ }

	};

	struct rb_tree_header : public rb_tree_node_base
	{
		size_t				node_count;

		rb_tree_header()
			: node_count(0)
		{ }

		void
		reset()
		{
			node_count = 0;
			parent = NULL;
			left = NULL;
			right = NULL;
		}

		void
		copy(const rb_tree_header& x)
		{
			color = x.color;
			parent = x.parent;
			left = x.left;
			right = x.right;
			node_count = x.node_count;
		}

	};

	template<typename T>
	struct rb_tree_node : public rb_tree_node_base
	{
		typedef	T		value_type;

		value_type	data;

		rb_tree_node(value_type val, base_ptr p, base_ptr l, base_ptr r, rb_tree_color c = RED)
		 : rb_tree_node_base(p, l, r, c), data(val)
		{ }

	};

	template<typename T>
	struct rb_tree_iterator
	{
		typedef T								value_type;
    	typedef T&								reference;
    	typedef T*								pointer;
    	typedef ptrdiff_t						difference_type;
		typedef bidirectional_iterator_tag		iterator_category;

    	typedef	rb_tree_iterator<T>				self;
    	typedef rb_tree_node_base::base_ptr		base_ptr;
    	typedef rb_tree_node<T>*				link_type;

		protected:
			base_ptr	_current;

		public:
			rb_tree_iterator()
				: _current()
			{ }

			rb_tree_iterator(base_ptr node)
				: _current(node)
			{ }

			rb_tree_iterator(const rb_tree_iterator& it)
				: _current(it._current)
			{ }

			~rb_tree_iterator(void)
			{ }

			reference
			operator*() const
			{ return (*static_cast<link_type>(_current)->data); }

			pointer
			operator->() const
			{ return (&static_cast<link_type>(_current)->data); }

			// rb_tree_iterator&
			// operator++()
			// {}

			// rb_tree_iterator
			// operator++(int)
			// {}

			// rb_tree_iterator&
			// operator--()
			// {}

			// rb_tree_iterator
			// operator--(int)
			// {}

			bool
			operator==(const rb_tree_iterator& it)
    		{ return (_current == it.current); }

			bool
			operator!=(const rb_tree_iterator& it)
    		{ return (_current != it.current); }

	};

	template<typename T, typename Key, typename Compare, typename Allocator = std::allocator<rb_tree_node<T> > >
	class rb_tree
	{
		public:
			typedef Allocator								allocator_type;
			typedef T										value_type;
			typedef Key										key_type;
			typedef rb_tree_node<T>							node;
			typedef rb_tree_node_base*						base_pointer;
			typedef node*									pointer;
			typedef const node*								const_pointer;
			typedef node&									reference;
			typedef const node&								const_reference;
			typedef size_t									size_type;
			typedef rb_tree_iterator<value_type>			iterator;
			typedef rb_tree_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		public:
			rb_tree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp)
			{
				_leaf.color = BLACK;
				_leaf.parent = NULL;
				_leaf.left = NULL;
				_leaf.right = NULL;
			}

			rb_tree(const rb_tree& x)
				: rb_tree(), _alloc(x._alloc), _comp(x._comp)
			{
				_header.copy(x._header);
			}

			~rb_tree()
			{ }

			size_t
			size() const
			{ return (_header.node_count); }

			size_t
			max_size()
			{ return (_alloc.max()); }

			rb_tree&
			operator=(const rb_tree& rhs)
			{
				if (this != &rhs)
				{
					_header.copy(rhs._header);
					_alloc = rhs._alloc;
				}
				return (*this);
			}

			ft::pair<iterator, bool>
			insert(const value_type& value)
			{
				pointer new_node = _alloc.allocate(1);
				key_type curr_key;
				base_pointer curr_node = _header.parent;
				base_pointer prev_node = NULL;

				if (curr_node == NULL)
				{
					_alloc.construct(new_node, node(value, &_header, &_leaf, &_leaf, BLACK));
					_header.parent = new_node;
					return (ft::make_pair(iterator(new_node), true));
				}
				else
				{
					while (curr_node != &_leaf)
					{
						curr_key = static_cast<pointer>(curr_node)->data.first;
						if (value.first == curr_key)
						{
							return (ft::make_pair(iterator(curr_node), false));
						}
						prev_node = curr_node;
						if (_comp(value.first, curr_key) == true)
						{
							curr_node = curr_node->left;
						}
						else
						{
							curr_node = curr_node->right;
						}
					}
					if (_comp(value.first, static_cast<pointer>(prev_node)->data.first) == true)
					{
						prev_node->left = new_node;
					}
					else
					{
						prev_node->right = new_node;
					}
					_alloc.construct(new_node, node(value, prev_node, &_leaf, &_leaf));
				}
				_header.node_count++;
				// insertFix();
				return (ft::make_pair(iterator(new_node), true));
			}

			void	display_tabs(int size)
			{
				while (size)
				{
					std::cout << "\x1b(0\x78\x1b(B\t";
					size--;
				}
			}

			void	display_tree()
			{
				base_pointer node = _header.parent;
				int height = 0;
				bool is_right = true;

				_display_tree(node, height, is_right);
			}

		private:
			rb_tree_node_base	_leaf;
			rb_tree_header		_header;
			allocator_type		_alloc;
			Compare				_comp;

			void
			_display_tree(base_pointer node, int height, bool is_right)
			{
				std::string horiz = "\x1b(0\x71\x1b(B";

				if (node == &_leaf)
					return ;
				display_tabs(height);
				// if (is_right)
				// 	std::cout << "\x1b(0\x74\x1b(B";
				// else
				// 	std::cout << "\x1b(0\x6d\x1b(B";
				// if (node->color == BLACK)
				// 	std::cout << "\033[41m";
				// else
				// 	std::cout << "\033[40m";
				// std::cout << node->color << "\033[49m";
				_display_tree(node->right, height + 1, true);
				_display_tree(node->left, height + 1, false);
			}


	};
	
}

#endif