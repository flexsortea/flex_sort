
#pragma once

#include <boost/static_assert.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{

	// this type is used to distinguish the filter ro
	struct sort_filter_root {};

	// the whole purpose of this structure is to avoid obscure calls
	// inside filters and recurisves functors 
	// all the wrapping is done once 
	template <typename Root, typename ThisType, typename SubLayer>
	struct sort_filter_stack
	{
		typedef typename boost::mpl::eval_if
		<
			boost::is_same<Root, sort_filter_root>, 
			boost::mpl::identity<ThisType>,  
			boost::mpl::identity<Root> 
		>::type root_type;

		// here we call back the top of the filter stack whereever we are in the stack
		// no overhead
		template <typename Iterator, typename Predicate>
		void top(Iterator first, Iterator last, Predicate pred, int depth)
		{
			// root_type is now going to be ThisType if Root was sort_filter_root
			// or remain Root, this way we forward the root correctly except in the case
			// we are the root in which case we pass on our type
			root_type::sort(first, last, pred, depth, root_type());
		}

		// used inside filters, we call the given functor (maybe another filter)
		// instead of going back to the top
		// we however forward correctly the root
		template <typename Iterator, typename Predicate>
		void down(Iterator first, Iterator last, Predicate pred, int depth)
		{
			// if we go down, the sublayer cannot be the void filter 
			BOOST_STATIC_ASSERT((boost::mpl::not_<boost::is_same<SubLayer, sort_void_filter> >::value));
			_down(first, last, pred, depth, root_type());
		}

	private:
		SubLayer _down;

	};


}