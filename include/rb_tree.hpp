#ifndef __RB_TREE__H__
#define __RB_TREE__H__

# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "utility.hpp"
# include <iostream>
# include <iomanip>
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
		typedef rb_tree_node_base*			base_ptr;
		typedef const rb_tree_node_base*	const_base_ptr;

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

	struct rb_tree_header
	{
		size_t				node_count;

		rb_tree_header()
		{
			_header.color = RED;
			reset();
		}

		void
		reset()
		{
			node_count = 0;
			_header.parent = NULL;
			_header.left = &_header;
			_header.right = &_header;
		}

		void
		copy(const rb_tree_header& x)
		{
			_header.color = x._header.color;
			_header.parent = x._header.parent;
			_header.left = x._header.left;
			_header.right = x._header.right;
			node_count = x.node_count;
		}


		protected:
			rb_tree_node_base	_header;

	};

	rb_tree_node_base*
	rb_minimum(rb_tree_node_base *node);

	rb_tree_node_base*
	rb_maximum(rb_tree_node_base *node);

	template<typename T>
	struct rb_tree_node : public rb_tree_node_base
	{
		typedef	T		value_type;

		value_type	data;

		rb_tree_node(value_type val, base_ptr p, base_ptr l, base_ptr r, rb_tree_color c = RED)
		 : rb_tree_node_base(p, l, r, c), data(val)
		{ }

		~rb_tree_node()
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

			self&
			operator=(const self& rhs)
			{
				_current = rhs.base();
				return (*this);
			}

			const base_ptr&
			base(void) const
			{ return (_current); }

			reference
			operator*() const
			{ return (static_cast<link_type>(_current)->data); }

			pointer
			operator->() const
			{ return (&static_cast<link_type>(_current)->data); }

			rb_tree_iterator&
			operator++()
			{
				if (_current->right->right != NULL)
				{
					_current = rb_minimum(_current->right);
					return (*this);
				}

    			base_ptr ptr = _current->parent;

				while ((ptr != ptr->parent) && (_current == ptr->right))
				{
					_current = ptr;
    				ptr = ptr->parent;
				}
				if (_current->right != ptr)
					_current = ptr;
				return (*this);
			}

			rb_tree_iterator
			operator++(int)
			{
				rb_tree_iterator tmp = *this;
				operator++();
				return (tmp);
			}

			rb_tree_iterator&
			operator--()
			{
				if (_current->left->left != 0)
    			{
        			_current = rb_maximum(_current->left);
    			}
				else
				{
					base_ptr ptr = _current->parent;
					while ((ptr != ptr->parent) && (_current == ptr->left))
					{
						_current = ptr;
						ptr = ptr->parent;
					}
					_current = ptr;
				}
				return (*this);
			}

			rb_tree_iterator
			operator--(int)
			{
				rb_tree_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			bool
			operator==(const rb_tree_iterator& it)
    		{ return (_current == it._current); }

			bool
			operator!=(const rb_tree_iterator& it)
    		{ return (_current != it._current); }

	};

	template<typename T>
	struct rb_tree_const_iterator
	{
		typedef T									value_type;
    	typedef const T&							reference;
    	typedef const T*							pointer;
    	typedef ptrdiff_t							difference_type;
		typedef bidirectional_iterator_tag			iterator_category;

		typedef rb_tree_iterator<T>					iterator;
    	typedef	rb_tree_const_iterator<T>			self;
    	typedef rb_tree_node_base::const_base_ptr	base_ptr;
    	typedef const rb_tree_node<T>*				link_type;

		protected:
			base_ptr	_current;

		public:
			rb_tree_const_iterator()
				: _current()
			{ }

			rb_tree_const_iterator(base_ptr node)
				: _current(node)
			{ }

			rb_tree_const_iterator(const iterator& it)
				: _current(it._current)
			{ }

			~rb_tree_const_iterator(void)
			{ }

			self&
			operator=(const self& rhs)
			{
				_current = rhs.base();
				return (*this);
			}

			const base_ptr&
			base(void) const
			{ return (_current); }

			reference
			operator*() const
			{ return (static_cast<link_type>(_current)->data); }

			pointer
			operator->() const
			{ return (&static_cast<link_type>(_current)->data); }

			self&
			operator++()
			{
				if (_current->right->right != NULL)
				{
					_current = rb_minimum(_current->right);
					return (*this);
				}

    			base_ptr ptr = _current->parent;

				while ((ptr != ptr->parent) && (_current == ptr->right))
				{
					_current = ptr;
    				ptr = ptr->parent;
				}
				if (_current->right != ptr)
					_current = ptr;
				return (*this);
			}

			self
			operator++(int)
			{
				self tmp = *this;
				operator++();
				return (tmp);
			}

			self&
			operator--()
			{
				if (_current->left->left != 0)
    			{
        			_current = rb_maximum(_current->left);
    			}
				else
				{
					base_ptr ptr = _current->parent;
					while ((ptr != ptr->parent) && (_current == ptr->left))
					{
						_current = ptr;
						ptr = ptr->parent;
					}
					_current = ptr;
				}
				return (*this);
			}

			self
			operator--(int)
			{
				self tmp = *this;
				operator--();
				return (tmp);
			}

			bool
			operator==(const self& it)
    		{ return (_current == it._current); }

			bool
			operator!=(const self& it)
    		{ return (_current != it._current); }

	};

	template<typename T, typename Key, typename Compare, typename Allocator = std::allocator<rb_tree_node<T> > >
	class rb_tree : public rb_tree_header
	{
		public:

			typedef Allocator								allocator_type;
			typedef T										value_type;
			typedef Key										key_type;
			typedef rb_tree_node_base*						base_pointer;
			typedef rb_tree_node<T>							Node;
			typedef Node*									pointer;
			typedef const Node*								const_pointer;
			typedef Node&									reference;
			typedef const Node&								const_reference;
			typedef size_t									size_type;
			typedef rb_tree_iterator<value_type>			iterator;
			typedef rb_tree_const_iterator<value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			rb_tree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp)
			{
				_leaf = _alloc.allocate(1);
				_alloc.construct(_leaf, Node(value_type(), NULL, NULL, NULL, BLACK));
			}

			rb_tree(const rb_tree& x)
				: _alloc(x._alloc), _comp(x._comp)
			{
				reset();
				for (const_iterator it = x.begin(); it != x.end(); it++)
				{
					insert(*it);
				}
			}

			~rb_tree()
			{
				clear();
				_alloc.destroy(_leaf);
				_alloc.deallocate(_leaf, 1);
			}

			size_t
			size() const
			{ return (node_count); }

			size_t
			max_size()
			{ return (_alloc.max()); }

			rb_tree&
			operator=(const rb_tree& rhs)
			{
				if (this != &rhs)
				{
					reset();
					for (const_iterator it = rhs.begin(); it != rhs.end(); it++)
					{
						insert(*it);
					}
				}
				return (*this);
			}

			base_pointer
			root()
			{ return (_header.parent); }

			base_pointer
			root() const
			{ return (_header.parent); }

			iterator
			begin()
			{ return (iterator(_header.left)); }

			const_iterator
			begin() const
			{ return (const_iterator(_header.left)); }

			iterator
			end()
			{ return (iterator(&_header)); }

			const_iterator
			end() const
			{ return (const_iterator(&_header)); }

			reverse_iterator
			rbegin()
			{ return (reverse_iterator(end())); }

			const_reverse_iterator
			rbegin() const
			{ return (const_reverse_iterator(end())); }

			reverse_iterator
			rend()
			{ return (reverse_iterator(begin())); }

			const_reverse_iterator
			rend() const
			{ return (const_reverse_iterator(begin())); }

			void
			clear()
			{
				pointer	root = static_cast<pointer>(_header.parent);

				if (root != NULL)
				{
					_clear(root);
					_alloc.destroy(root);
					_alloc.deallocate(root, 1);
					reset();
				}
			}

			void
			erase(base_pointer node)
			{
				base_pointer	ptr1 = node, ptr2;
				rb_tree_color	orig_color = ptr1->color;

				if (node->left == _leaf)
				{
					ptr2 = node->right;
					_node_transplant(node, node->right);
				}
				else if (node->right == _leaf)
				{
					ptr2 = node->left;
					_node_transplant(node, node->left);
				}
				else
				{
					ptr1 = rb_minimum(node->right);
					orig_color = ptr1->color;
					ptr2 = ptr1->right;
					if (ptr1->parent == node)
					{
						ptr1->parent = ptr1;
					}
					else
					{
						_node_transplant(ptr1, ptr1->right);
						ptr1->right = node->right;
						ptr1->right->parent = ptr1;
					}
					_node_transplant(node, ptr1);
					ptr1->left = node->left;
					ptr1->left->parent = ptr1;
					ptr1->color = node->color;
				}
				_alloc.destroy(static_cast<pointer>(node));
				_alloc.deallocate(static_cast<pointer>(node), 1);
				if (orig_color == BLACK)
				{
					_delete_fix(ptr2);
				}
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
					_alloc.construct(new_node, Node(value, &_header, _leaf, _leaf, BLACK));
					_header.parent = new_node;
					return (ft::make_pair(iterator(new_node), true));
				}
				else
				{
					while (curr_node != _leaf)
					{
						curr_key = static_cast<pointer>(curr_node)->data.first;
						if (value.first == curr_key)
						{
							_alloc.deallocate(new_node, 1);
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
					_alloc.construct(new_node, Node(value, prev_node, _leaf, _leaf));
				}
				node_count++;
				_insert_fix(new_node);
				_header.left = rb_minimum(_header.parent);
				_header.right = rb_maximum(_header.parent);
				return (ft::make_pair(iterator(new_node), true));
			}

			void
			swap(rb_tree& other)
			{
				pointer			tmp;
				rb_tree_header	htmp;

				tmp = _leaf;
				_leaf = other._leaf;
				other._leaf = tmp;

				htmp.copy(*this);
				copy(other);
				other.copy(htmp);
			}

			iterator
			find(const Key& key)
			{
				if (root() == NULL)
					return (end());
				return (iterator(_find(root(), key)));
			}

			const_iterator
			find(const Key& key) const
			{
				if (root() == NULL)
					return (end());
				return (const_iterator(_find(root(), key)));
			}

			void
			print_tree(void)
			{
				if (root() == NULL)
					return ;
				_print_tree("", root());
			}


		private:
			void
			_node_transplant(base_pointer x, base_pointer y)
			{
				if (x->parent == NULL)
				{
					_header.parent = y;
				}
				else if (x == x->parent->left)
				{
					x->parent->left = y;
				}
				else
				{
					x->parent->right = y;
				}
				y->parent = x->parent;
			}

			void
			_delete_fix(base_pointer node)
			{
				base_pointer	ptr;
				
				while ((node != _header.parent) && (node->color == BLACK))
				{
					if (node == node->parent->left)
					{
    					ptr = node->parent->right;
						if (ptr->color == RED)
						{
							ptr->color = BLACK;
							node->parent->color = RED;
        					_left_rotate(node->parent);
							ptr = node->parent->right;
						}
						if ((ptr->left->color == BLACK) && (ptr->right->color == BLACK))
						{
							ptr->color = RED;
							node = node->parent;
						}
						else
						{
							if (ptr->right->color == BLACK)
							{
								ptr->left->color = BLACK;
								ptr->color = RED;
								_right_rotate(ptr);
								ptr = node->parent->right;
							}
							ptr->color = node->parent->color;
							node->parent->color = BLACK;
							ptr->right->color = BLACK;
							_left_rotate(node->parent);
							node = _header.parent;
						}
					}
					else
					{
						ptr = node->parent->left;
						if (ptr->color == RED)
						{
							ptr->color = BLACK;
							node->parent->color = RED;
							_right_rotate(node->parent);
							ptr = node->parent->left;
						}
						if ((ptr->right->color == BLACK) && (ptr->right->color == BLACK))
						{
							ptr->color = RED;
							node = node->parent;
						}
						else
						{
							if (ptr->left->color == BLACK)
							{
								ptr->right->color = BLACK;
								ptr->color = RED;
								_left_rotate(ptr);
								ptr = node->parent->left;
							}
							ptr->color = node->parent->color;
							node->parent->color = BLACK;
							ptr->left->color = BLACK;
							_right_rotate(node->parent);
							node = _header.parent;
						}
					}
				}
				node->color = BLACK;
			}

			void
			_insert_fix(base_pointer node)
			{
				base_pointer ptr;

				while (node->parent->color == RED)
				{
    				if (node->parent == node->parent->parent->right)
					{
						ptr = node->parent->parent->left;
						if (ptr->color == RED)
						{
							ptr->color = BLACK;
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								_right_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							_left_rotate(node->parent->parent);
						}
					}
					else
					{
        				ptr = node->parent->parent->right;

        				if (ptr->color == RED)
						{
        					ptr->color = BLACK;
        					node->parent->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								_left_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							_right_rotate(node->parent->parent);
						}
    				}
    				if (node == _header.parent)
        				break;
				}
    			_header.parent->color = BLACK;
			}

			void
			_print_key(pointer node)
			{
				std::string color;

				if (node->color == BLACK)
					color = "\033[40m";
				else
					color = "\033[41m";
				if (node == _leaf)
					std::cout << color << "NIL";
				else
					std::cout << color << node->data.first;
				std::cout << "\033[49m" << std::endl;
			}

			void
			_print_tree(const std::string& prefix, base_pointer node, bool is_right = true)
			{
				std::cout << prefix;
				std::cout << (is_right ? "└──" : "├──" );
				_print_key(static_cast<pointer>(node));
				if (node == _leaf)
					return ;
				_print_tree(prefix + (is_right ? "\t" : "│\t"), node->left, false);
				_print_tree(prefix + (is_right ? "\t" : "│\t"), node->right, true);
			}

			size_t
			_count_height(base_pointer node, size_t height = 0, size_t max_height = 0)
			{
				if (node == _leaf)
				{
					if (height > max_height)
						return (height);
					return (max_height);
				}
				max_height = _count_height(node->left, height + 1, max_height);
				return (_count_height(node->right, height + 1, max_height));
			}

			size_t
			_count_leaf(base_pointer node)
			{
				int count = 0;

				if (node == _leaf)
					return (1);
				count += _count_leaf(node->left);
				count += _count_leaf(node->right);
				return (count);
			}

			void
			_clear(base_pointer node)
			{
				pointer ptr = NULL;

				if (node->left != _leaf)
				{
					_clear(node->left);
					ptr = static_cast<pointer>(node->left);
					_alloc.destroy(ptr);
					_alloc.deallocate(ptr, 1);
				}
				if (node->right != _leaf)
				{
					_clear(node->right);
					ptr = static_cast<pointer>(node->right);
					_alloc.destroy(ptr);
					_alloc.deallocate(ptr, 1);
				}
			}

			const rb_tree_node_base*
			_find(base_pointer node, const Key& to_find) const
			{
				if (node == _leaf)
					return (&_header);

				const Key curr_key = static_cast<pointer>(node)->data.first;

				if (curr_key == to_find)
					return (node);
				else if (_comp(to_find, curr_key) == true)
					return (_find(node->left, to_find));
				else
					return (_find(node->right, to_find));
			}

			base_pointer
			_find(base_pointer node, const Key& to_find)
			{
				if (node == _leaf)
					return (&_header);

				const Key curr_key = static_cast<pointer>(node)->data.first;

				if (curr_key == to_find)
					return (node);
				else if (_comp(to_find, curr_key) == true)
					return (_find(node->left, to_find));
				else
					return (_find(node->right, to_find));
			}

			void
			_right_rotate(base_pointer node)
			{
				base_pointer ptr = node->left;

    			node->left = ptr->right;
				if (ptr->right != _leaf)
				{
					ptr->right->parent = node;
				}
				ptr->parent = node->parent;
				if (node->parent == &_header)
				{
    				_header.parent = ptr;
				}
				else if (node == node->parent->right)
				{
					node->parent->right = ptr;
				}
				else
				{
					node->parent->left = ptr;
				}
				ptr->right = node;
				node->parent = ptr;
			}

			void
			_left_rotate(base_pointer node)
			{
				base_pointer ptr = node->right;

    			node->right = ptr->left;
				if (ptr->left != _leaf)
				{
					ptr->left->parent = node;
				}
				ptr->parent = node->parent;
				if (node->parent == &_header)
				{
    				_header.parent = ptr;
				}
				else if (node == node->parent->left)
				{
					node->parent->left = ptr;
				}
				else
				{
					node->parent->right = ptr;
				}
				ptr->left = node;
				node->parent = ptr;
			}

			pointer				_leaf;
			allocator_type		_alloc;
			Compare				_comp;

	};

	rb_tree_node_base*
	rb_minimum(rb_tree_node_base *node)
	{
		while (node->left->left != NULL)
		{
			node = node->left;
		}
		return (node);
	}

	rb_tree_node_base*
	rb_maximum(rb_tree_node_base *node)
	{
		while (node->right->right != NULL)
		{
			node = node->right;
		}
		return (node);
	}
	
	const rb_tree_node_base*
	rb_minimum(const rb_tree_node_base *node)
	{
		while (node->left->left != NULL)
		{
			node = node->left;
		}
		return (node);
	}

	const rb_tree_node_base*
	rb_maximum(const rb_tree_node_base *node)
	{
		while (node->right->right != NULL)
		{
			node = node->right;
		}
		return (node);
	}
}

#endif