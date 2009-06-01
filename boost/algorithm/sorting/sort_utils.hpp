
#pragma once

#include <functional>
#include <iterator>

#include <boost/assert.hpp>

namespace boost
{

	// returns true, if and only if the list is empty or ordered
	// predicate is a binary operator that returns true when the first parameter is ordered relatively to the second parameter
	template <typename Iterator, typename Predicate>
	bool is_ordered(Iterator first, Iterator last, Predicate pred)
	{
		if (first == last)
			return true; // an empty list is ordered

		// we need to do the above test, because our loop assumes that
		// there is at least one element
		for(Iterator current = first, next; 
			++(next = current) != last;
			current = next)
		{
			if (!pred(*current, *next))
				return false;
		}

		return true;

	}

	// implementation of the above function with <=
	template <typename Iterator>
	bool is_ordered(Iterator first, Iterator last)
	{
		return is_ordered(first, last, std::less_equal<std::iterator_traits<Iterator>::value_type>());
	}

}