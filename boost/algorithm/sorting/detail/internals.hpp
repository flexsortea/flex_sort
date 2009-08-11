
#pragma once

#include <iterator>

#include <boost/algorithm/sorting/filter_stack.hpp>

namespace boost
{
namespace detail
{



	// implements a predicateless operator() if one with a predicate is available
	template <typename T, template <typename> class P>
	struct default_predicate : T
	{
		typedef default_predicate<T, P> this_type;

		template <typename Iterator>
		void operator()(Iterator first, Iterator last)
		{
			typedef typename std::iterator_traits<Iterator>::value_type value_type;

			// we don't want to pass this type as it would be useless to go back to here
			// the underlying type is going to be a better candidate for the stack's top
			T::sort(first, last, P<value_type>(), 0, boost::sort_filter_root());
		}
	};

	template <typename T>
	struct sort_traits
	{
		typedef T this_type;
	};

	template <typename T>
	struct implement_filter_operator : virtual sort_traits<T>
	{
		template <typename Iterator, typename Predicate, typename Root>
		bool operator()(Iterator first, Iterator last, Predicate pred, int depth, Root r)
		{
			return T::sort(first, last, pred, depth, r);
		}
	};

	template <typename T>
	struct implement_predicate_operator : virtual sort_traits<T>
	{
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator first, Iterator last, Predicate pred, int depth)
		{
			return T::sort(first, last, pred, depth);
		}
	};

	template <typename T>
	struct implement_sorter_operator : virtual sort_traits<T>
	{
		template <typename Iterator, typename Predicate, typename Root>
		void operator()(Iterator first, Iterator last, Predicate pred, int depth, Root r)
		{
			T::sort(first, last, pred, depth, r);
		}
	};


}
}