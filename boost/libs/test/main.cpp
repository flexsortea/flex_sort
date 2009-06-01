

#include <boost/test/unit_test.hpp>

using boost::unit_test::test_suite;

#include "sort_utils_tests.hpp"
#include "insert_sort_tests.hpp"
#include "quick_sort_tests.hpp"


test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
	test_suite* test = BOOST_TEST_SUITE( "Main test suite" );


	test->add( BOOST_TEST_CASE( &sort_utils_tests ));
	test->add( BOOST_TEST_CASE( &insert_sort_tests ));
	test->add( BOOST_TEST_CASE( &quick_sort_tests ));

	return test;
}