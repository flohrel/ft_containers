#ifndef __TYPE_TRAITS__H__
#define __TYPE_TRAITS__H__

namespace ft
{
	template< bool B, class T = void >
	struct enable_if { };
 
	template< class T >
	struct enable_if< true, T > { typedef T type; };

	template< class T, T v >
	struct integral_constant
	{
    	static const T value = v;

		typedef T							value_type;
  		typedef integral_constant< T, v >	type;

    	operator value_type( void ) const { return value; }
	};

	typedef integral_constant< bool, true >		true_type;
	typedef integral_constant< bool, false >	false_type;

	template< typename T >
	struct is_integral : public false_type { };

	template<>
	struct is_integral< char > : public true_type { };

	template<>
	struct is_integral< bool > : public true_type { };

	template<>
	struct is_integral< int > : public true_type { };

	template<>
	struct is_integral< long > : public true_type { };

	template<>
	struct is_integral< long long > : public true_type { };

	template<>
	struct is_integral< short > : public true_type { };

	template<>
	struct is_integral< wchar_t > : public true_type { };

	template<>
	struct is_integral< unsigned char > : public true_type { };

	template<>
	struct is_integral< unsigned int > : public true_type { };

	template<>
	struct is_integral< unsigned long > : public true_type { };

	template<>
	struct is_integral< unsigned long long > : public true_type { };

	template<>
	struct is_integral< unsigned short > : public true_type { };

}

#endif