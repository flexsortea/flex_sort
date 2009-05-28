
#pragma once

#include <functional>
#include <iterator>

#include <boost/assert.hpp>

namespace boost
{

	// returns true, if and only if the list is empty or ordered
	// predicate is a binary operator that returns true when the first parameter is lower than the second parameter
	template <typename Iterator, typename Predicate>
	bool is_ordered(Iterator first, Iterator last, Predicate pred)
	{

		Iterator current = first;
		Iterator next;

		while(current != last)
		{
			next = current;
			++next;

			BOOST_ASSERT(current != next);

			// next didn't become the last element and the current is !predicate the next
			// means the list is unordered
			if ((next != last) && !pred(*current, *next))
				return false;

			// we can be here, if and only if the predicate holds true
			// or we have reached the end
			BOOST_ASSERT(((next != last) && pred(*current, *next)) || (next == last));

			current = next;
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