
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
			(*static_cast<T *>(this))(first, last, P<value_type>(), 0, boost::sort_filter_root());
		}
	};



}
}