#include "header.hpp"

int	main( void )
{
	unit_test::TestRunner	runner;

	unit_test::vector_suite();
	// stack_suite();
	// map_suite();
	// set_suite();

	runner.run_all();
	return (0);
}
