
#pragma once

#include <iterator>

#include <boost/assert.hpp>
#include <boost/swap.hpp>

#include <boost/algorithm/sorting/flex_tags.hpp>

namespace boost
{


	// only works on collections of size >= 2
	// used as a default fallback in most recursive functors
	// otherwise we would get infinite recursion
	struct trivial_sort
	{

		struct sorter_type : forward_iterator_sorter_tag {};

		template <typename Iterator, typename Predicate, typename Root>
		void operator()(Iterator first, Iterator last, Predicate pred, int, Root)
		{
			if (first != last)
			{
				typedef std::iterator_traits<Iterator>::difference_type difference_type;

				difference_type size = std::distance(first, last);

				if (size > static_cast<difference_type>(1))
				{
					// no more than 2
					BOOST_ASSERT(size == static_cast<difference_type>(2));

					Iterator second = first;
					++second;

					// we swap if the order is wrong
					if (!pred(*first, *second))
					{
						boost::swap(*first, *second);
					}

					// nothing more
				}

			}

		}

	};


}