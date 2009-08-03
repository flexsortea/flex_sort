
#pragma once

#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/algorithm/sorting/sort_filter.hpp>
#include <boost/algorithm/sorting/detail/sort_filter_ground.hpp>

namespace boost
{

	template <int MaxDepth, typename Sorter, typename NextFilter>
	struct sort_filter_ground : sort_filter<detail::sort_filter_ground<MaxDepth>, Sorter, NextFilter> {};


}