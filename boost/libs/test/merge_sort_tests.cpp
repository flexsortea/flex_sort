
#include "merge_sort_tests.hpp"

#include <vector>

#include <boost/algorithm/sorting/mergers.hpp>
#include <boost/algorithm/sorting/merge_sort.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include "sort_test_cases.hpp"
#include "test_vectors.hpp"

using namespace std;
using namespace boost;


struct test_with_merger
{
	template <typename Merger>
	void operator()(Merger)
	{

		vector<int> empty;

		trivial_test_case<boost::merge_sort<Merger> >()(empty);

		large_test_case<boost::merge_sort<Merger>, 100000>()(empty);

		vector<int> yeah;

		// this is some 
		yeah.push_back(3);
		yeah.push_back(10);
		yeah.push_back(1);
		yeah.push_back(0);

		sort_whatever_case<boost::merge_sort<Merger> >()(yeah);

		vector<unsigned char> crypto_randomnes(crypto_random_256_bytes, crypto_random_256_bytes + sizeof(crypto_random_256_bytes));

		sort_whatever_case<boost::merge_sort<Merger> >()(crypto_randomnes);
	}
};



void merge_sort_tests(void)
{

	typedef mpl::vector<boost::merger_inplace, boost::merger> mergers_types;
	mpl::for_each<mergers_types>(test_with_merger());


}