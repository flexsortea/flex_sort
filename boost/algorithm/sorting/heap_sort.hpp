
#pragma once

#include <algorithm>
#include <iterator>

#include <boost/algorithm/sorting/flex_sort_tags.hpp>

namespace boost
{

	// the STL already comes with everything necessary to build heap_sort
	struct heap_sort
	{

		// heap sort is not recursive
		typedef sorter_tag sorter_type;

		template <typename Iterator>
		void operator()(Iterator first, Iterator last)
		{

		}

		template <typename Iterator, typename Predicate>
		void operator()(Iterator first, Iterator last, Predicate pred)
		{
			std::make_heap(first, last, pred);
			std::sort_heap(first, last, pred);
		}
	};

}