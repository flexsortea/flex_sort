
#pragma once

#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{

namespace detail
{

	template <int MaximumDepth>
	struct sort_filter_ground : boost::detail::implement_predicate_operator<sort_filter_ground<MaximumDepth> >
	{
		// the cutoff happens at the specified size
		// TODO: actually estimate the depth compared to the size
		template <typename Iterator, typename Predicate>
		static bool sort(Iterator, Iterator, Predicate, int depth) 
		{
			// the depth must be greater than 0
			BOOST_STATIC_ASSERT(MaximumDepth > 0);
			return depth >= MaximumDepth;
		}
	};

}

}