
#pragma once

#include <functional>
#include <iterator>

#include <boost/algorithm/sorting/flex_sort_tags.hpp>
#include <boost/algorithm/sorting/detail/flex_sort_internals.hpp>

namespace boost
{
	
	namespace detail
	{
		struct insert_sort_core 
		{

			// not recursive, requires a bidir iterator
			struct sorter_type : bidirectional_iterator_sorter_tag {};

			template <typename Iterator, typename Predicate>
			void operator()(Iterator first, Iterator last, Predicate pred)
			{
				// don't want to work on an empty list
				if (first == last)
					return;

				typedef typename std::iterator_traits<Iterator>::value_type value_type;

				// because our loop, like in is_ordered, assumes at least one element
				for(Iterator next = first; ++next != last;)
				{

					value_type v = *next;

					if (pred(v, *first))
					{
						// looks like this value is smaller than the front
						// time for Mr. Rotate to make some room
						Iterator next_next = next;
						std::rotate(first, next, ++next_next);

						// now that we slided everything, we can put the new front
						*first = v;
					}
					else
					{

						// we need the inner_next outside the for, because when the loop is complete
						// we're going to put the value into whatever it's pointing 
						Iterator inner_next = next;

						// say hello to Mr. O(n*n)
						for(Iterator inner_first = next; pred(v, *--inner_first); inner_next = inner_first)
						{
							// sliding stuff as long as the predicate holds true
							// (note that we reversed the parameters to the predicate as a trick to consider equal elements ordered)
							*inner_next = *inner_first;
						}

						*inner_next = v;
					}

				}


			}

		};

	}


	struct insert_sort : detail::default_predicate<detail::insert_sort_core, std::less>
	{

	};
	

}