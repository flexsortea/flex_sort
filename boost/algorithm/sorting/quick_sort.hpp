
#pragma once

namespace boost
{

	template 
	<
		int SmallThreshold,
		int DepthFallback,
		typename Swapper,
		typename SmallSorter
	>
	struct quick_sort
	{
		template <typename Iterator, typename Predicate>
		Iterator split(Iterator first, Iterator last, Predicate pred)
		{



		}

		template <typename Iterator>
		void pivot_transition(Iterator & pivot)
		{
			
		}

		template <typename Iterator, typename Predicate>
		void post_process(Iterator first, Iterator last, Predicate pred)
		{

		}
	};

}