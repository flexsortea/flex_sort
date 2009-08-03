
#pragma once

namespace boost
{

namespace detail
{

	template <int MaximumDepth>
	struct sort_filter_ground
	{
		// the cutoff happens at the specified size
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator, Iterator, Predicate, int depth) const
		{
			// the depth must be greater than 0
			BOOST_STATIC_ASSERT(MaximumDepth > 0);
			return depth >= MaximumDepth;
		}
	};

}

}