

#include <boost/test/unit_test.hpp>

using boost::unit_test::test_suite;

#include "sort_utils_test.hpp"

test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
	test_suite* test = BOOST_TEST_SUITE( "Main test suite" );


	test->add( BOOST_TEST_CASE( &sort_utils_tests ));

	return test;
}