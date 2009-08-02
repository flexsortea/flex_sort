
#include "insert_sort_tests.hpp"

#include <vector>

#include <boost/algorithm/sorting/insert_sort.hpp>

#include "sort_test_cases.hpp"
#include "test_vectors.hpp"


void insert_sort_tests(void)
{
	std::vector<int> empty;

	trivial_test_case<boost::insert_sort>()(empty);

	std::vector<int> yeah;

	// this is some 
	yeah.push_back(3);
	yeah.push_back(10);
	yeah.push_back(1);
	yeah.push_back(0);

	sort_whatever_case<boost::insert_sort>()(yeah);

	std::vector<unsigned char> crypto_randomnes(crypto_random_256_bytes, crypto_random_256_bytes + sizeof(crypto_random_256_bytes));

	sort_whatever_case<boost::insert_sort>()(crypto_randomnes);



}