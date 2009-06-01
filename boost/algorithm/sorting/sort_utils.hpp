
#pragma once

#include <functional>
#include <iterator>

namespace boost
{

	// by default, we sort with " < "
	template <typename T>
	struct default_order : std::less<T>	{ };

	template <typename Iterator>
	struct default_iterator_order : default_order<typename std::iterator_traits<Iterator>::value_type> { };

	// returns true, if and only if the list is empty or ordered
	// predicate is a binary operator that returns true when the first parameter is ordered relatively to the second parameter
	template <typename Iterator, typename Predicate>
	bool is_ordered(Iterator first, Iterator last, Predicate pred)
	{
		if (first == last)
			return true; // an empty list is ordered

		// we need to do the above test, because our loop assumes that
		// there is at least one element
		for(Iterator current = first, next; ++(next = current) != last;	current = next)
		{
			if (pred(*next, *current))
				return false;
		}

		return true;

	}

	// implementation of the above function with <=
	template <typename Iterator>
	bool is_ordered(Iterator first, Iterator last)
	{
		return is_ordered(first, last, default_iterator_order<Iterator>());
	}

}