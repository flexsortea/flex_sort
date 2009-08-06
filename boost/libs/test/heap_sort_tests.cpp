
#include "heap_sort_tests.hpp"

#include <vector>

#include <boost/algorithm/sorting/heap_sort.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include "sort_test_cases.hpp"
#include "test_vectors.hpp"

using namespace std;
using namespace boost;


void heap_sort_tests(void)
{

	std::vector<int> empty;

	trivial_test_case<boost::heap_sort>()(empty);

	large_test_case<boost::heap_sort, 10000>()(empty);

	std::vector<int> yeah;

	// this is some 
	yeah.push_back(3);
	yeah.push_back(10);
	yeah.push_back(1);
	yeah.push_back(0);

	sort_whatever_case<boost::heap_sort>()(yeah);

	std::vector<unsigned char> crypto_randomnes(crypto_random_256_bytes, crypto_random_256_bytes + sizeof(crypto_random_256_bytes));

	sort_whatever_case<boost::heap_sort>()(crypto_randomnes);


}