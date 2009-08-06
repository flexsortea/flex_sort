
#pragma once

#include <algorithm>

#include <boost/algorithm/sorting/utils.hpp>
#include <boost/test/test_tools.hpp>

#include <boost/lambda/lambda.hpp>


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

template <typename SortAlgorithm, int Size>
struct large_test_case
{

	template <typename Collection>
	void operator()(Collection &)
	{
		typedef typename Collection::iterator iterator_type;
		typedef typename Collection::value_type value_type;

		typedef SortAlgorithm sorter_type;

		sorter_type sort_to_test;

		// constant values
		Collection c(Size, 3);

		// must not crash, must not throw
		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));

		// we increase the size to one element with default constructor
		
		value_type v = 0;
		std::generate(c.begin(), c.end(), boost::lambda::var(v)++);
		BOOST_ASSERT(boost::is_ordered(c.begin(), c.end()));

		BOOST_REQUIRE_NO_THROW(sort_to_test(c.begin(), c.end()));
		BOOST_ASSERT(boost::is_ordered(c.begin(), c.end()));

		// now we reverse
		Collection c2(c.size());
		std::copy(c.begin(), c.end(), c2.rbegin());
		BOOST_ASSERT(!boost::is_ordered(c2.begin(), c2.end()));

		BOOST_REQUIRE_NO_THROW(sort_to_test(c2.begin(), c2.end()));

		// obviously, must be sorted
		BOOST_ASSERT(boost::is_ordered(c2.begin(), c2.end()));
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