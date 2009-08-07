
#pragma once

#include <functional>
#include <iterator>

#include <boost/swap.hpp>
#include <boost/assert.hpp>



#include <boost/algorithm/sorting/flex_tags.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{

	namespace detail
	{

		template<typename PivotSelector, typename Partitionner>
		struct quick_sort_core
		{

			typedef quick_sort_core<PivotSelector, Partitionner> this_type;

			// if we're the root, then we cast to ourselves
			// being root means that Root is of type sort_root

			// quicksort is a typical recursive sort
			struct sorter_type : recursive_sorter_tag, random_iterator_sorter_tag {};

			template <typename Iterator, typename Predicate, typename Root>
			void operator()(Iterator first, Iterator last, Predicate pred, int depth, Root)
			{

				// we need to be able to stop the recursion by ourselves at some point
				typedef typename std::iterator_traits<Iterator>::difference_type distance_type;

				typedef Iterator iterator_type;
				
				typedef typename std::iterator_traits<Iterator>::value_type value_type;	

				// we choose a suitable pivot
				iterator_type pivot = _select_pivot(first, last, pred);

				BOOST_ASSERT(pivot != last);

				// we back up the pivot at the first position in the array
				boost::swap(*first, *pivot);

				// and we partition skipping the first element which is the placeholder
				// for the pivot's value
				iterator_type par_start = first;
				++par_start;

				pivot = _partition(par_start, last, std::bind2nd(pred, *first));

				// pivot restoration
				--pivot;
				boost::swap(*pivot, *first);

				typedef sort_get_root<Root, this_type>::root_type root_type;

				// here goes the recursion, do not pass root_rype as parameter,
				// otherwisey ou will "reroot" the search tree
				(*reinterpret_cast<root_type *>(this))(first, pivot, pred, ++depth, Root());
				(*reinterpret_cast<root_type *>(this))(++pivot, last, pred, depth, Root());
			}

		private:
			PivotSelector _select_pivot;
			Partitionner _partition;
			
		};
	}


	template<typename PivotSelector, typename Partitionner>
	struct quick_sort :	detail::default_predicate<detail::quick_sort_core<PivotSelector, Partitionner>, std::less>
	{

	};



}