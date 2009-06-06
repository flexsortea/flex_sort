
#pragma once

namespace boost
{

	struct quick_sort
	{
		template <typename Iterator, typename Predicate>
		void sort(Iterator first, Iterator last, Predicate pred, typename std::iterator_traits<Iterator>::distance_type distance_hint = -1, unsigned int depth = 0)
		{
			std::sort(first, last, pred);
		}
	};

}