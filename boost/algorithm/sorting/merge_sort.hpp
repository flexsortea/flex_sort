
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

		typedef merge_sort_core<Merger> this_type;

		template <typename Iterator, typename Predicate, typename Root>
		void operator()(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			typedef std::iterator_traits<Iterator>::difference_type difference_type;

			difference_type size = std::distance(first, last);

			// we get the iterator in the middle
			Iterator middle = first;
			std::advance(middle, size / 2);

			typedef sort_get_root<Root, this_type>::root_type root_type;

			// we recursively process, do not pass root_rype as parameter,
			// otherwisey ou will "reroot" the search tree
			(*reinterpret_cast<root_type *>(this))(first, middle, pred, ++depth, Root());
			(*reinterpret_cast<root_type *>(this))(middle, last, pred, depth, Root());

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