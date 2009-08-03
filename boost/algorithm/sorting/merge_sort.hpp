
#pragma once

#include <iterator>
#include <list>

namespace boost
{



	template 
	<
		int SmallThreshold,
		int DepthFallback
		typename Swapper,
		typename SmallSorter
	>
	struct inplace_merge_sort
	{
		template <typename Iterator, typename Predicate>
		Iterator split(Iterator first, Iterator last, Predicate pred)
		{

			std::iterator_traits<Iterator>::distance_type l = std::distance(first, last);

			if (l < SmallThreshold)
			{
				SmallSorter()(first, last, pred);				
			}
			else
			{
				std::advance(
			}

		}

		template <typename Iterator>
		void pivot_transition(Iterator & pivot)
		{
			// nop in the case of merge sort
		}

		template <typename Iterator, typename Predicate>
		void post_process(Iterator first, Iterator last, Predicate pred)
		{
			std::inplace_merge(first, last, pred);
		}
	};

}