
#pragma once

#include <algorithm>

namespace boost
{

	// we use the std::partition function
	struct default_partitionner
	{
		template <typename Iterator, typename Predicate>
		Iterator operator()(Iterator first, Iterator last, Predicate pred)
		{
			return std::partition(first, last, pred);
		}
	};

}