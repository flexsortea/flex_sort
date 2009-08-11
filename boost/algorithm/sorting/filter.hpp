
#pragma once

#include <boost/algorithm/sorting/filter_stack.hpp>

#include <boost/algorithm/sorting/detail/filter_basics.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{

	// a filter that will either apply TrueFilter of FalseFilter
	// TrueFilter will be applied when the predicate returns true
	// FalseFilter will be applied when the predicate returns true
	// the operator will return true if and only if TrueFilter is applied
	template <typename FilterPredicate, typename TrueFilter, typename FalseFilter>
	struct sort_block_filter : detail::implement_filter_operator<sort_block_filter<FilterPredicate, TrueFilter, FalseFilter> >
	{

		typedef sort_block_filter<FilterPredicate, TrueFilter, FalseFilter> this_type;

		template <typename Iterator, typename Predicate, typename Root>
		static bool sort(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			bool result = false;

			FilterPredicate filter;

			if (filter(first, last, pred, depth))
			{
				boost::sort_filter_stack<Root, this_type, TrueFilter> filter_stack;
				filter_stack.down(first, last, pred, depth);
				result = true;
			}
			else
			{
				boost::sort_filter_stack<Root, this_type, FalseFilter> filter_stack;
				filter_stack.down(first, last, pred, depth);
			}

			return result;

		}

	};

	// a filter that will optionally apply TrueFilter and always pass on to NextFilter
	// TrueFilter will be applied when the predicate returns true
	// NextFilter is always applied
	// the operator will return true if and only if TrueFilter is applied
	template <typename FilterPredicate, typename TrueFilter, typename NextFilter>
	struct sort_pass_filter : detail::implement_filter_operator<sort_pass_filter<FilterPredicate, TrueFilter, NextFilter> >
	{

		typedef sort_pass_filter<FilterPredicate, TrueFilter, NextFilter> this_type;

		template <typename Iterator, typename Predicate, typename Root>
		static bool sort(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			bool result = false;

			boost::sort_filter_stack<Root, this_type> filter_stack;

			FilterPredicate filter;

			if (filter(first, last, pred, depth))
			{
				boost::sort_filter_stack<Root, this_type, TrueFilter> filter_stack;
				filter_stack.down(first, last, pred, depth);
				result = true;
			}

			boost::sort_filter_stack<Root, this_type, NextFilter> filter_stack;

			filter_stack.down(first, last, pred, depth);

			return result;

		}

	};

	// use this when you need a stack just to go up and not to go down
	struct sort_void_filter
	{
		template <typename Iterator, typename Predicate, typename Root>
		static bool sort(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			return false;
		}
	};



}