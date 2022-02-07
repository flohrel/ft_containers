#ifndef __VECTOR__H__
#define __VECTOR__H__

namespace ft
{
	class vector
	{
		public:
			vector( void );
			vector( vector const & src );
			~vector( void );
	
			vector &	operator=( vector const & rhs );
	
	};
	
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
}

#endif