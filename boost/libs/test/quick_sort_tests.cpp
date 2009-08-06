
#include "quick_sort_tests.hpp"

#include <vector>

#include <boost/algorithm/sorting/quick_sort.hpp>
#include <boost/algorithm/sorting/pivot_selector.hpp>
#include <boost/algorithm/sorting/partitionner.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include "sort_test_cases.hpp"
#include "test_vectors.hpp"

using namespace std;
using namespace boost;

struct test_with_pivot
{
	template <typename PivotSelector>
	void operator()(PivotSelector)
	{

		vector<int> empty;

		trivial_test_case<boost::quick_sort<PivotSelector, boost::default_partitionner> >()(empty);

		// nothing big because in some cases we get quadratic behaviour
		large_test_case<boost::quick_sort<PivotSelector, boost::default_partitionner>, 100>()(empty);

		vector<int> yeah;

		// this is some 
		yeah.push_back(3);
		yeah.push_back(10);
		yeah.push_back(1);
		yeah.push_back(0);

		sort_whatever_case<boost::quick_sort<PivotSelector, boost::default_partitionner> >()(yeah);

		vector<unsigned char> crypto_randomnes(crypto_random_256_bytes, crypto_random_256_bytes + sizeof(crypto_random_256_bytes));

		sort_whatever_case<boost::quick_sort<PivotSelector, boost::default_partitionner> >()(crypto_randomnes);
	}
};



void quick_sort_tests(void)
{

	typedef mpl::vector<boost::pivot_first, boost::pivot_last, boost::pivot_middle, boost::pivot_median_of_three> pivots_types;
	mpl::for_each<pivots_types>(test_with_pivot());


}