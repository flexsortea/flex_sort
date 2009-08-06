
#pragma once

#include <iterator>
#include <list>

#include <boost/algorithm/sorting/flex_tags.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{

namespace detail
{
	// the STL already comes with everything necessary to build heap_sort
	template <typename Merger>
	struct merge_sort_core
	{

		// merge sort is recursive
		struct sorter_type : recursive_sorter_tag, random_iterator_sorter_tag {};

		template <typename Iterator, typename Predicate>
		void operator()(Iterator first, Iterator last, Predicate pred, int depth)
		{
			if (first == last)
				return;

			typedef std::iterator_traits<Iterator>::difference_type difference_type;

			difference_type size = std::distance(first, last);

			if (size == 1)
				return;

			if (size == 2)
			{
				Iterator second = first;
				++second;
				if (!pred(*first, *second))
				{
					boost::swap(*first, *second);
				}

				return;
			}

			// we get the iterator in the middle
			Iterator middle = first;
			std::advance(middle, size / 2);

			// we recursively process
			(*this)(first, middle, pred, ++depth);
			(*this)(middle, last, pred, depth);

			// and we merge !
			_merge(first, middle, last, pred);

		}

	private:
		Merger _merge;
	};
}

	template <typename Merger>
	struct merge_sort : detail::default_predicate<detail::merge_sort_core<Merger>, std::less>
	{

	};

}