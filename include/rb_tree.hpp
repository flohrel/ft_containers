#ifndef __RB_TREE__H__
#define __RB_TREE__H__

# include "iterator_traits.hpp"

namespace ft
{
	enum	rb_tree_color
	{
		RED,
		BLACK
	};

	template <typename T>
	struct rb_tree_node
	{
		typedef rb_tree_node<T>	node;

		rb_tree_color	color;
		node*			parent;
		node*			left;
		node*			right;
		T				data;

		rb_tree_node(enum rb_tree_color def_color = RED)
			: color(def_color), parent(NULL), left(NULL), right(NULL), data()
		{ }

		rb_tree_node(const node& x)
		{ *this = x; }

		~rb_tree_node()
		{ }

		node&
		operator=(const node& rhs)
		{
			if (this != &rhs)
			{
				color = rhs.color;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				data = rhs.data;
			}
			return (*this);
		}

	};
	template<typename T, typename Compare, typename Alloc = std::allocator<rb_tree_node<T> > >
	class rb_tree
	{
		public:
			typedef T				value_type;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef T*				pointer;
			typedef size_t			size_type;
			typedef rb_tree_node<T>	node;

		public:
			rb_tree()
				: _TNULL(BLACK), _root(&_TNULL), _leftmost(&_TNULL), _rightmost(&_TNULL), _count(0)
			{ }

			rb_tree(const rb_tree& x)
				: _TNULL(BLACK), _root(x._root), _leftmost(x._leftmost), _rightmost(x._rightmost), _count(x._count)
			{ }

			~rb_tree()
			{ }

			size_t
			size() const
			{
				return (_count);
			}

		private:
			node		_TNULL;
			node*		_root;
			node*		_leftmost;
			node*		_rightmost;
			size_type	_count;

	};
	
}

#endif