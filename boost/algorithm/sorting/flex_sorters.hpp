
#pragma once

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/algorithm/sorting/detail/flex_sort_internals.hpp>
#include <boost/algorithm/sorting/flex_sort_tags.hpp>

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
	struct safe_recursive_sorter : dual_sorter<sort_rec_too_deep<DepthThreshold>, MainSorter, OverflowSorter> 
	{
		safe_recursive_sorter(void)
		{
			// it doesn't make sense to protect against recursion overflow if the main algorithm isn't recursive
			BOOST_STATIC_ASSERT((boost::is_convertible<typename MainSorter::sorter_type, boost::recursive_sorter_tag>::type));
		}

	};


	// if the call recursion reaches DepthThreshold we will user OverflowSorter instead of MainSorter
	// in both cases, if the size of the collection is below Smallthreshold we will use Smallsorter
	template
	<
		unsigned int DepthThreshold,
		unsigned int SmallThreshold,
		typename MainSorter,
		typename SmallSorter,
		typename OverflowSorter
	>
	struct safe_recursive_small_optimized_sorter : 
		safe_recursive_sorter
		<
			DepthThreshold, 
			small_optimized_sorter<SmallThreshold, MainSorter, SmallSorter>,
			small_optimized_sorter<SmallThreshold, OverflowSorter, SmallSorter>
		>
	{};

}