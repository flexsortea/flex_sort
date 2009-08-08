
#pragma once

#include <functional>

#include <boost/algorithm/sorting/trivial_sort.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>
#include <boost/algorithm/sorting/detail/quick_sort_core.hpp>

namespace boost
{

	template <typename PivotSelector, typename Partitionner>
	struct quick_sort : detail::default_predicate<sort_filter_cutoff<2, 
		trivial_sort, 
		detail::quick_sort_core<PivotSelector, Partitionner>
		>,
		std::less>
	{

	};


}