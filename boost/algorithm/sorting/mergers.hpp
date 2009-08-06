
#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

namespace boost
{


	// there are different merge strategies

	// no memory overhead but generally slower than the regular merge
	struct merger_inplace
	{
		template <typename Iterator, typename Predicate>
		void operator()(Iterator first, Iterator middle, Iterator last, Predicate pred)
		{
			// the stl is delivered with an inplace_merge, no need to reinvent
			// the wheel
			std::inplace_merge(first, middle, last, pred);
		}
	};


	struct merger
	{
		template <typename Iterator, typename Predicate>
		void operator()(Iterator first, Iterator middle, Iterator last, Predicate pred)
		{
			typedef typename std::iterator_traits<Iterator>::value_type value_type;

			// we copy everything to two different temporary vectors 
			std::vector<value_type> left(first, middle);
			std::vector<value_type> right(middle, last);

			// and then we merge into the original destination
			std::merge(left.begin(), left.end(), right.begin(), right.end(), first, pred);
		}
	};


}