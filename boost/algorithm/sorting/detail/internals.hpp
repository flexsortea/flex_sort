
#pragma once

#include <iterator>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
namespace detail
{

	struct sort_root {};

	template <typename Root, typename ThisType>
	struct sort_get_root
	{
		typedef typename boost::mpl::eval_if
		<
			boost::is_same<Root, sort_root>, 
			boost::mpl::identity<ThisType>,  
			boost::mpl::identity<Root> 
		>::type root_type;
	};

	// implements a predicateless operator() if one with a predicate is available
	template <typename T, template <typename> class P>
	struct default_predicate : T
	{
		typedef default_predicate<T, P> this_type;

		template <typename Iterator>
		void operator()(Iterator first, Iterator last)
		{
			typedef typename std::iterator_traits<Iterator>::value_type value_type;
			(*static_cast<T *>(this))(first, last, P<value_type>(), 0, boost::detail::sort_root());
		}
	};



}
}