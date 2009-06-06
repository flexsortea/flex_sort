
#pragma once

#include <iterator>

#include <boost/algorithm/sorting/flex_sorters.hpp>
#include <boost/algorithm/sorting/insert_sort.hpp>
#include <boost/algorithm/sorting/quick_sort.hpp>
#include <boost/algorithm/sorting/heap_sort.hpp>

namespace boost
{

	// this is a typical introspective sort
	template <unsigned int DepthFallBack, unsigned int SmallThreshold>
	struct intro_sort : protected_small_optimized_sorter<DepthFallBack, SmallThreshold, default_quick_sort, insert_sort, heap_sort> {};

	// example of call
	// std::vector<int> v;
	// ...
	// flex_sort<intro_sort<15, 10>>(v.begin(), v.end());
	template 
	<
		typename Sorter,  
		typename Iterator, 
		typename Predicate 
	>
	void flex_sort(Iterator first, Iterator last, Predicate pred, typename std::iterator_traits<Iterator>::distance_type distance_hint = -1)
	{
		Sorter()(first, last, distance_hint, pred, 0);
	}



}