
#pragma once

#include <iterator>

namespace boost
{
namespace detail
{

	// implements a predicateless operator() if one with a predicate is available
	template <typename T, template <typename> class P>
	struct default_predicate : T
	{
		template <typename Iterator>
		void operator()(Iterator first, Iterator last)
		{
			typedef typename std::iterator_traits<Iterator>::value_type value_type;
			(*static_cast<T *>(this))(first, last, P<value_type>(), 0);
		}
	};



}
}