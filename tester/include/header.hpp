#ifndef __HEADER__H__
# define __HEADER__H__

# include "libunitcpp.hpp"

# ifdef STD
#  include <map>
#  include <stack>
#  include <vector>
#  include <set>
   namespace ft = std;
# else
#  include "map.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#  include "set.hpp"
# endif

namespace unit_test {
namespace vector_suite {

void	suite_registrar( void );

}
}

#endif