
#pragma once

#include <functional>
#include <iterator>

#include <boost/swap.hpp>
#include <boost/assert.hpp>

#include <boost/algorithm/sorting/flex_sort_tags.hpp>
#include <boost/algorithm/sorting/detail/flex_sort_internals.hpp>

namespace boost
{

	namespace detail
	{
		template<typename PivotSelector, typename Partitionner>
		struct quick_sort_core
		{

			// quicksort is a typical recursive sort
			struct sorter_type : recursive_sorter_tag, random_iterator_sorter_tag {};

			template <typename Iterator, typename Predicate>
			void operator()(Iterator first, Iterator last, Predicate pred)
			{

				if (first == last)
					return;

				typedef Iterator iterator_type;
				typedef typename std::iterator_traits<Iterator>::difference_type distance_type;
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

				// pivot restauration
				--pivot;
				boost::swap(*pivot, *first);

				// here goes the recursion
				(*this)(first, pivot, pred);
				(*this)(++pivot, last, pred);

			}

		private:
			PivotSelector _select_pivot;
			Partitionner _partition;
		};
	}


	template<typename PivotSelector, typename Partitionner>
	struct quick_sort : detail::default_predicate<detail::quick_sort_core<PivotSelector, Partitionner>, std::less>
	{

	};



}