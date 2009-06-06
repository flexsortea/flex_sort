
#pragma once

#include <boost/algorithm/sorting/detail/flex_sort_internals.hpp>
namespace boost
{

	// if the size of the collection is below SmallThreshold
	// we will sort using Smallsorter instead of MainSorter
	template
	<
		unsigned int SmallTreshold,
		typename MainSorter,
		typename SmallSorter
	>
	struct small_optimized_sorter : dual_sorter<sort_input_small_enough<SmallThreshold>, MainSorter, SmallSorter> {	};

	// if the call recursion reaches DepthThreshold we will user OverflowSorter instead of MainSorter
	template
	<
		unsigned int DepthThreshold,
		typename MainSorter,
		typename OverflowSorter
	>
	struct protected_sorter : dual_sorter<sort_rec_too_deep<DepthThreshold>, MainSorter, OverflowSorter> {};


	// if the call recursion reaches DepthThreshold we will user OverflowSorter instead of MainSorter
	// in both cases, if the size of the collection is below Smallthreshold we will use Smallsorter
	template
	<
		unsigned int DepthThreshold,
		unsigned int SmallTreshold,
		typename MainSorter,
		typename SmallSorter,
		typename OverflowSorter
	>
	struct protected_small_optimized_sorter : 
		dual_sorter
		<
			sort_rec_too_deep<DepthThreshold>, 
			small_optimized_sorter<SmallThreshold, MainSorter, SmallSorter>,
			small_optimized_sorter<SmallThreshold, OverflowSorter, SmallSorter>
		>
	{

	};

}