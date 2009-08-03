
#pragma once

#include <iterator>

#include <boost/algorithm/sorting/pivot_selector.hpp>
#include <boost/algorithm/sorting/partitionner.hpp>

#include <boost/algorithm/sorting/insert_sort.hpp>

#include <boost/algorithm/sorting/quick_sort.hpp>
#include <boost/algorithm/sorting/heap_sort.hpp>

#include <boost/algorithm/sorting/filter_cutoff.hpp>
#include <boost/algorithm/sorting/filter_ground.hpp>

namespace boost
{

	typedef detail::default_predicate<sort_filter_cutoff
	<
		18, 
		detail::insert_sort_core, 
		sort_filter_ground<30, detail::heap_sort_core, detail::quick_sort_core<pivot_median_of_three, default_partitionner> > 
	>,
	std::less> flex_sort;



}