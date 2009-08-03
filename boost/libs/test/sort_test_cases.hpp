
#pragma once

#include <boost/algorithm/sorting/utils.hpp>
#include <boost/test/test_tools.hpp>

// in this test case, we work only on empty, and identical elements up to two
// this catches the obvious bugs

template <typename SortAlgorithm>
struct trivial_test_case
{

	template <typename Collection>
	void operator()(Collection &)
	{
		typedef typename Collection::iterator iterator_type;
		typedef typename Collection::value_type value_type;

		typedef SortAlgorithm sorter_type;

		sorter_type sort_to_test;


		Collection c;

		// must not crash, must not throw
		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));

		// we increase the size to one element with default constructor
		c.resize(1);
		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));

		// and to two
		c.resize(2);
		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));

		// obviously, must be sorted
		BOOST_ASSERT(boost::is_ordered(c.begin(), c.end()));
	}


};

template <typename SortAlgorithm>
struct sort_whatever_case
{

	template <typename Collection>
	void operator()(Collection & c)
	{
		typedef typename Collection::iterator iterator_type;
		typedef typename Collection::value_type value_type;

		typedef SortAlgorithm sorter_type;

		sorter_type sort_to_test;

		// we get some input and we make sure it sorts right, no throw, thanks
		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));

		// sorted?
		BOOST_ASSERT(boost::is_ordered(c.begin(), c.end()));

		// we do it twice, must be ok, or it means we can't handle sorted data
		// or that we messed up memory 
		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));

		BOOST_ASSERT(boost::is_ordered(c.begin(), c.end()));

	}

};