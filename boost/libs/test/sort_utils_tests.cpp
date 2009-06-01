
#include "sort_utils_tests.hpp"

#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <map>

#include <boost/algorithm/sorting/sort_utils.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/cstdint.hpp>

#include <boost/lambda/lambda.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include <limits>

using namespace std;
using namespace boost;

template <typename Collection>
static void generate_sorted(Collection & c)
{
	typename Collection::value_type i = 0;
	generate(c.begin(), c.end(), lambda::var(i)++);
}


struct basic_tests
{

	static const int _max_iterations = 1000;

	template <typename Collection>
	void do_it(Collection & c)
	{
		typedef typename Collection::value_type value_type;

		// BOOST_STATIC_ASSERT((numeric_limits<value_type>::max() >= (static_cast<value_type>(_max_iterations + 1))));

		// an empty collection must be seen as ordered
		BOOST_CHECK(is_ordered(c.begin(), c.end()));

		for(value_type i = 0; i < _max_iterations; ++i)
		{
			// as we go along it stays ordered
			c.push_back(i);
			BOOST_CHECK(is_ordered(c.begin(), c.end()));
		}

		value_type v = 0;

		Collection::iterator prev_end = c.end();
		--prev_end;

		for(typename Collection::iterator it = c.begin();
			it !=prev_end;
			++it, ++v)
		{
			*it = _max_iterations + 1;

			// we flip one entry at the time and is becomes unordered
			BOOST_CHECK(!is_ordered(c.begin(), c.end()));

			*it = v;
		}

		// much bigger, note that we make sure it's not going to be a problem for 16-bit
		// values with a size below 2^15
		c.resize(32000);

		generate_sorted(c);

		BOOST_CHECK(is_ordered(c.begin(), c.end()));

		// some test with equal values, must always be ordered
		fill(c.begin(), c.end(), 0);
		BOOST_CHECK(is_ordered(c.begin(), c.end()));
		fill(c.begin(), c.end(), numeric_limits<value_type>::min());
		BOOST_CHECK(is_ordered(c.begin(), c.end()));
		fill(c.begin(), c.end(), numeric_limits<value_type>::max());
		BOOST_CHECK(is_ordered(c.begin(), c.end()));

		c.clear();

		// Highway to the danger zone! Ride into the danger zone! lalalalalalalala!
		c.push_back(numeric_limits<value_type>::min());
		c.push_back(numeric_limits<value_type>::max());

		BOOST_CHECK(is_ordered(c.begin(), c.end()));

		// we swap the ordered list
		typename Collection::iterator next = c.begin();
		iter_swap(c.begin(), ++next);

		// it becomes unordered
		BOOST_CHECK(!is_ordered(c.begin(), c.end()));
	}

	template <typename Int>
	void operator()(Int p)
	{
		do_it(vector<Int>());
		do_it(list<Int>());
		do_it(deque<Int>());
	}

};

void sort_utils_tests(void)
{

	typedef mpl::vector<int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t> int_test_types;

	mpl::for_each<int_test_types>(basic_tests());



}