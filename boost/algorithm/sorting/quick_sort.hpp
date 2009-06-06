
#pragma once

#include <iterator>

#include <boost/swap.hpp>
#include <boost/assert.hpp>

#include <boost/algorithm/sorting/flex_sort_tags.hpp>

namespace boost
{


	template
	<
		typename PivotSelector,
		typename Partitionner
	>
	struct quick_sort
	{

		// quicksort is a typical recursive sort
		typedef recursive_sorter_tag sorter_type;

		template <typename Iterator, typename Predicate>
		void operator()(Iterator first, Iterator last, Predicate pred, typename std::iterator_traits<Iterator>::distance_type distance_hint = -1, unsigned int depth = 0)
		{
			
			typedef Iterator iterator_type;
			typedef typename std::iterator_traits<Iterator>::difference_type distance_type;
			typedef typename std::iterator_traits<Iterator>::value_type value_type;	

			// we choose a suitable pivot
			iterator_type pivot = _select_pivot(first, last, pred);

			// we back up the pivot at the first position in the array
			value_type pivot_value = *pivot;
			boost::swap(*first, pivot_value);

			// and we partition skipping the first element which is the placeholder
			// for the pivot's value
			iterator_type par_start = first;
			++par_start;

			pivot = _partition(par_start, last, std::bind2nd(pred, pivot_value));

			// the iterator must be "greater" or equal to the pivot
			BOOST_ASSERT(pred(pivot_value, *pivot));

			// pivot restauration
			--pivot;
			boost::swap(pivot, *first);

			// here goes the recursion
			(*this)(first, pivot, pred, distance_hint, ++depth);
			(*this)(++pivot, last, pred, distance_hint, depth);

		}

	private:
		PivotSelector _select_pivot;
		Partitionner _partition;
	};

}