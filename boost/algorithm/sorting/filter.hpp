
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
	struct sort_block_filter
	{

		typedef sort_block_filter<FilterPredicate, TrueFilter, FalseFilter> this_type;

		template <typename Iterator, typename Predicate, typename Root>
		bool operator()(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{

			bool result = false;

			boost::sort_filter_stack<Root, this_type> filter_stack;

			if (_pred(first, last, pred, depth))
			{
				filter_stack.down(_true, first, last, pred, depth);
				result = true;
			}
			else
			{
				filter_stack.down(_false, first, last, pred, depth);
			}

			return result;

		}

	private:
		FilterPredicate _pred;
		TrueFilter _true;
		FalseFilter _false;
	};

	// a filter that will optionally apply TrueFilter and always pass on to NextFilter
	// TrueFilter will be applied when the predicate returns true
	// NextFilter is always applied
	// the operator will return true if and only if TrueFilter is applied
	template <typename FilterPredicate, typename TrueFilter, typename NextFilter>
	struct sort_pass_filter
	{

		typedef sort_pass_filter<FilterPredicate, TrueFilter, NextFilter> this_type;

		template <typename Iterator, typename Predicate, typename Root>
		bool operator()(Iterator first, Iterator last, Predicate pred, int depth, Root)
		{
			bool result = false;

			boost::sort_filter_stack<Root, this_type> filter_stack;

			if (_pred(first, last, pred, depth))
			{
				filter_stack.down(_true, first, last, pred, depth);
				result = true;
			}

			filter_stack.down(_next, first, last, pred, depth);

			return result;

		}

	private:
		FilterPredicate _pred;
		TrueFilter _true;
		NextFilter _next;
	};



}