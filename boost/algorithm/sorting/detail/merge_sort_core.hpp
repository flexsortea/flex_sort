
#pragma once

#include <iterator>

#include <boost/algorithm/sorting/flex_tags.hpp>
#include <boost/algorithm/sorting/filter_stack.hpp>
#include <boost/algorithm/sorting/filter_cutoff.hpp>

namespace boost
{
namespace detail
{

	template <typename Merger>
	struct merge_sort_core
	{

		// merge sort is recursive
		struct sorter_type : recursive_sorter_tag, random_iterator_sorter_tag {};

		typedef merge_sort_core<Merger> this_type;

		template <typename Iterator, typename Predicate, typename Root>
		void operator()(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			typedef std::iterator_traits<Iterator>::difference_type difference_type;

			difference_type size = std::distance(first, last);

			// we get the iterator in the middle
			Iterator middle = first;
			std::advance(middle, size / 2);

			sort_filter_stack<Root, this_type> filter_stack;

			// we recursively process, do not pass root_rype as parameter,
			// otherwisey ou will "reroot" the search tree
			filter_stack.top(*this, first, middle, pred, ++depth);
			filter_stack.top(*this, middle, last, pred, depth);

			// and we merge !
			_merge(first, middle, last, pred);

		}

	private:
		Merger _merge;
	};


}
}