
#pragma once

#include <iterator>

#include <boost/static_assert.hpp>

namespace boost
{

namespace detail
{

	template <int Cutoff>
	struct sort_filter_cutoff
	{
		// the cutoff happens at the specified size
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator first, Iterator last, Predicate, int) const
		{
			// we have a specialization for 0, so the cutoff must be at least 1
			BOOST_STATIC_ASSERT(Cutoff > 0);
			return std::distance(first, last) <= Cutoff;
		}
	};

	// optimization for empty lists
	template <>
	struct sort_filter_cutoff<0>
	{
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator first, Iterator last, Predicate, int) const
		{
			return first == last;
		}
	};


}

}