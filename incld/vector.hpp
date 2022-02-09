#ifndef __VECTOR__H__
# define __VECTOR__H__

# include <memory>
# include "iterator.h"

namespace ft
{
	template < typename T, typename Allocator = std::allocator< T > >
	class vector
	{
		public:
			typedef typename T							value_type;
			typedef typename Allocator 					allocator_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			

			vector( void );
			vector( vector const & src );
			~vector( void );
	
			vector &	operator=( vector const & rhs );
		
		
		vector::vector( void )
		{
			/* Content */
			return;
		}
		
		vector::vector( vector const & src )
		{
			*this = src;
			return;
		}
		
		vector::~vector( void )
		{
			/* Content */
			return;
		}
		
		vector &	vector::operator=( vector const & rhs )
		{
			/* Content */
			return (*this);
		}
	};
}

#endif