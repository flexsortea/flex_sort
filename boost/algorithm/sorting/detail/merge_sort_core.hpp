
#pragma once

#include <iterator>

#include <boost/algorithm/sorting/flex_tags.hpp>
#include <boost/algorithm/sorting/filter_stack.hpp>
#include <boost/algorithm/sorting/filter_cutoff.hpp>

#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{
namespace detail
{

	template <typename Merger>
	struct merge_sort_core : boost::detail::implement_sorter_operator<merge_sort_core<Merger> >
	{

		// merge sort is recursive
		struct sorter_type : recursive_sorter_tag, random_iterator_sorter_tag {};

		template <typename Iterator, typename Predicate, typename Root>
		static void sort(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			typedef std::iterator_traits<Iterator>::difference_type difference_type;

			difference_type size = std::distance(first, last);

			// we get the iterator in the middle
			Iterator middle = first;
			std::advance(middle, size / 2);

			sort_filter_stack<Root, this_type, sort_void_filter> filter_stack;

			// we recursively process, do not pass root_rype as parameter,
			// otherwisey ou will "reroot" the search tree
			filter_stack.top(first, middle, pred, ++depth);
			filter_stack.top(middle, last, pred, depth);

			// and we merge !
			Merger()(first, middle, last, pred);

		}

	};


}
}