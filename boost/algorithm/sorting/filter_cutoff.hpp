
#pragma once

#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/algorithm/sorting/filter.hpp>
#include <boost/algorithm/sorting/detail/filter_cutoff.hpp>

namespace boost
{

	template <int Cutoff, typename Sorter, typename NextFilter>
	struct sort_filter_cutoff : sort_filter<detail::sort_filter_cutoff<Cutoff>, Sorter, NextFilter> {};


}