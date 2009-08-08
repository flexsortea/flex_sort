
#pragma once

#include <functional>

#include <boost/algorithm/sorting/trivial_sort.hpp>

#include <boost/algorithm/sorting/detail/internals.hpp>
#include <boost/algorithm/sorting/detail/merge_sort_core.hpp>

namespace boost
{

	template <typename Merger>
	struct merge_sort : detail::default_predicate<sort_filter_cutoff<2, 
		trivial_sort, 
		detail::merge_sort_core<Merger>
	>,
	std::less>
	{

	};


}