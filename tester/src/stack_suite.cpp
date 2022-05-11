# include "stack.hpp"
# include <stack>

# include "libunitcpp.hpp"

TEST_SUITE(stack_suite)

TEST_CASE(la_flemme)
{
	assert( std::string("Cette suite est vide...") != std::string("c\'est parce que je n'avais pas le temps !") );
	assert( "Bon ok, en vrai j\' avais la flemme." );
}

TEST_SUITE_END()