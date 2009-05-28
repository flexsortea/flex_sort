
#pragma once

#include <iterator>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include "detail/flex_sort_internals.hpp"

namespace boost
{



	template
	<
		int SmallThreshold,
		int DepthFallback,
		// functor called when size < SmallThreshold
		typename SmallSorter,
		// functor called when depth >= DepthFallback
		typename FallbackSorter,
		// called when a split is requested
		typename Splitter,
		// called when the pivot must be processed between the two partitions calls
		typename PivotTransiter,
		// called after the two partitions have been processed
		typename PostProcessor,
		// functor used to swap two elements, by default std::iter_swap
		typename Swapper = std::iter_swap
	>
	struct sorter
	{


	public:
		// abstract sorter, doesn't directly process iterators
		// therfore only inherits from sorter_category
		typedef boost::sorter_tag sorter_category;

	private:
		template <typename DistanceType, typename Iterator>
		void update_distance_hint(DistanceType & distance_hint, Iterator first, Iterator last)
		{
			// this helps us avoiding computing the distance everytime
			if (distance_hint == -1)
			{
				distance_hint = std::distance(first, last);
			}

		}

	private:
		// called when the small collections need to be processed with the SmallSorter
		// other collections will be processed by Functor
		template <typename Iterator, typename Predicate, typename Functor>
		Iterator small_check_functor(Iterator first, 
			Iterator last, 
			Predicate pred, 
			Functor f, 
			std::iterator_traits<Iterator>::distance_type distance_hint = -1)
		{
			Iterator result = last;

			update_distance_hint(distance_hint, first, last);

			if (distance_hint < SmallThreshold)
			{
				_small_sort(first, last, pred, distance_hint);
			}
			else
			{
				result = f(first, last, pred, distance_hint);
			}

			return result;
		}

	public:
		template <typename Iterator, typename Predicate>
		void fallback_sort(Iterator first, Iterator last, Predicate pred, std::iterator_traits<Iterator>::distance_type distance_hint = -1)
		{
			small_check_functor(first, last, pred, _fallback_sort, distance_hint);
		}

	public:
		// makes two collections out of one according the splitter template
		// if the size is below the smallthreshol, smallsorter will process the list
		template <typename Iterator, typename Predicate>
		Iterator split(Iterator first, Iterator last, Predicate pred, std::iterator_traits<Iterator>::distance_type & distance_hint = -1)
		{
			return small_check_functor(first, last, pred, _splitter, distance_hint);
		}

		template <typename Iterator>
		void pivot_transition(Iterator & pivot)
		{
			_pivot_transition(pivot);
		}

		template <typename Iterator, typename Predicate>
		void post_process(Iterator first, Iterator last, Predicate pred, std::iterator_traits<Iterator>::distance_type distance_hint = -1)
		{
			update_distance_hint(distance_hint, first, last);
			_post_process(first, last, pred);
		}

	private:
		SmallSorter _small_sort;
		FallbackSorter _fallback_sort;
		Splitter _splitter;
		PivotTransiter _pivot_transition; 
		PostProcessor _post_process;
	};

	template 
	<
		int SmallThreshold,
		int DepthFallback, 
		typename Sorter,  
		typename Iterator, 
		typename Predicate 
	>
	void flex_sort(Iterator first, Iterator last, Predicate pred, int depth = 0, std::iterator_traits<Iterator>::distance_type distance_hint = -1)
	{

		// it doesn't make sens to fallback for a depth of 0 (i.e. immediately)
		BOOST_STATIC_ASSERT(DepthFallBack > 0);

		// we check that we got a sorter
		BOOST_STATIC_ASSERT(boost::is_convertible<typename Sorter::sorter_category, boost::sorter_tag>::type);
		
		// we validate the iterator agains the sorter engines used
		BOOST_STATIC_ASSERT(boost::is_converible<std::iterator_traits<iterator>::iterator_category, typename Sorter::sorter_category>::type);

		
		typedef typename Sorter::small_sorter_type small_sorter_type;
		typedef typename Sorter::splitter_type splitter_type;
		typedef typename Sorter::pivot_transiter_type pivot_transiter_type;
		typedef typename Sorter::post_processor_type post_processor_type;
		typedef typename Sorter::swapper_type swapper_type;

		// we build the actual sorter engine according to the sorter parameters
		typedef sorter
		<
			SmallThreshold, 
			DepthFallback, 
			small_sorter_type, 
			splitter_type, 
			pivot_transiter_type, 
			post_processor_type,
			swapper_type 
		> sorter_type;

		if (depth >= DepthFallback)
		{
			sorter_type::fallback_sort()(first, last, pred, distance_hint);
		}
		else
		{
			// the split can be a quicksort partition or a simple "divide the list in two"
			Iterator pivot = sorter_type::split(first, last, pred);

			// pivot == last when the distance between first and last is below SmallThreshold
			// in which case a specific algorithm is used for small collections
			if (pivot != last)
			{
				// we deep one step further, we increase the depth for both calls
				++depth;

				// left part
				flex_sort<SmallThreshold, DepthFallback, Sorter, Iterator, Predicate>(first, pivot, pred, depth, distance_hint);

				// nop or ++pivot depending on the algorithm
				sorter_type::pivot_transition(pivot);

				// right part
				flex_sort<SmallThreshold, DepthFallback, Sorter, Iterator, Predicate>(pivot, last, pred, depth, distance_hint);

				// this can be a nop (quicksort)
				// or a merge (merge_sort)
				sorter_type::post_process(first, pivot, last, pred);
			}
		}

	}

}