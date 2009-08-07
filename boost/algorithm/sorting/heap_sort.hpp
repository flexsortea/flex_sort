
#pragma once

#include <algorithm>
#include <functional>
#include <iterator>

#include <boost/algorithm/sorting/flex_tags.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{

	namespace detail
	{
		// the STL already comes with everything necessary to build heap_sort
		struct heap_sort_core
		{

			// heap sort is not recursive
			struct sorter_type : random_iterator_sorter_tag {};

			template <typename Iterator, typename Predicate, typename Root>
			void operator()(Iterator first, Iterator last, Predicate pred, int, Root)
			{
				std::make_heap(first, last, pred);
				std::sort_heap(first, last, pred);
			}
		};
	}


	struct heap_sort : detail::default_predicate<detail::heap_sort_core, std::less>
	{

	};


}