
#pragma once

#include <iterator>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>

namespace boost
{
namespace detail
{

	template <typename DistanceType, typename Iterator>
	static DistanceType update_distance_hint(DistanceType distance_hint, Iterator first, Iterator last)
	{
		DistanceType result = distance_hint;

		// this helps us avoiding computing the distance every time
		if (result == -1)
		{
			result = std::distance(first, last);
		}

		BOOST_ASSERT(result != -1);

		return result;
	}

	// mnemotechnic way to remember
	// the decision maker decides if we must go for Plan B
	// (ie if DecisionMaker() returns true, we use SorterB)
	template
	<
		template <unsigned int> class DecisionMaker,
		typename SorterA,
		typename SorterB
	>
	struct dual_sorter
	{

	public:
		dual_sorter(void)
		{
			// Are you trying to choose between two identical sorters? :)
			BOOST_STATIC_ASSERT((boost::mpl::not_<boost::is_same<SorterA, SorterB>::type>::type));
		}

	public:
		template <typename Iterator, typename Predicate>
		void operator()(Iterator first, Iterator last, Predicate pred, typename std::iterator_traits<Iterator>::distance_type distance_hint = -1, unsigned int depth = 0)
		{
			distance_hint = update_distance_hint(distance_hint, first, last);

			// if the decision maker says "yes", we go for plan B
			if (_decide(distance_hint, depth))
			{
				_sort_b(first, last, pred, distance_hint, depth + 1);
			}
			else
			{
				_sort_a(first, last, pred, distance_hint, depth + 1);
			}

		}

	private:
		DecisionMaker _decide;

		SorterA _sort_a;
		SorterB _sort_b;

	};




}
}