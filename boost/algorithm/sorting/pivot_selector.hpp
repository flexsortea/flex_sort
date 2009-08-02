
#pragma once

namespace boost
{

	// take the first element as a pivot
	struct pivot_first
	{
		template <typename Iterator, typename Predicate>
		Iterator operator()(Iterator first, Iterator, Predicate)
		{
			return first;
		}
	};

	// take the last element as a pivot
	struct pivot_last
	{
		template <typename Iterator, typename Predicate>
		Iterator operator()(Iterator first, Iterator last, Predicate)
		{
			if (first == last)
				return first;

			return --last;
		}
	};

	// take the element in the middle as a pivot
	struct pivot_middle
	{
		template <typename Iterator, typename Predicate>
		Iterator operator()(Iterator first, Iterator last, Predicate)
		{
			typedef typename std::iterator_traits<Iterator>::difference_type distance_type;
			distance_type length = std::distance(first, last);

			// we use the pivot in the middle
			Iterator result(first);
			std::advance(result, length / 2);

			BOOST_ASSERT(result != last);

			return result;
		}
	};

	// take the median of the first, middle and last element as a pivot
	struct pivot_median_of_three
	{

		template <typename Iterator, typename Predicate>
		Iterator operator()(Iterator first, Iterator last, Predicate pred)
		{
			if (first == last)
				return first;

			// get the middle
			Iterator middle = pivot_middle()(first, last, pred);

			Iterator previous_last = last;
			--previous_last;

			Iterator median_of_three = middle;

			if (pred(*first, *previous_last))
			{
				// first element is "less" than the last
				if (pred(*middle, *first))
				{
					// order is middle < first < last
					median_of_three = first;
				}
				else
				{
					if (pred(*previous_last, *middle))
					{
						// order is first < last < middle
						median_of_three = previous_last;
					}
				}
			}
			else
			{
				// the last element is "less" than the firt
				if (pred(*middle, *previous_last))
				{
					// order is middle < last < first
					median_of_three = previous_last;
				}
				else
				{

					if (pred(*middle, *first))
					{
						// order is middle < first < last
						median_of_three = first;
					}

				}

			}

			return median_of_three;
		}

	};

	// when you don't need a pivot finder, use this, it will cause a compilation error if you were
	// wrong about not needing a pivot finder ;)
	struct pivot_void
	{
		template <typename Iterator, typename Predicate>
		Iterator operator()(Iterator first, Iterator last, Predicate)
		{
			BOOST_STATIC_ASSERT(false);
		}
	};
	

}