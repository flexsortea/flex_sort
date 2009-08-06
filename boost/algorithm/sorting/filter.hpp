
#pragma once

namespace boost
{

	// a filter that will either apply TrueFilter of FalseFilter
	// TrueFilter will be applied when the predicate returns true
	// FalseFilter will be applied when the predicate returns true
	// the operator will return true if and only if TrueFilter is applied
	template <typename FilterPredicate, typename TrueFilter, typename FalseFilter>
	struct sort_block_filter
	{

		template <typename Iterator, typename Predicate>
		bool operator()(Iterator first, Iterator last, Predicate pred, int depth = 0)
		{
			bool result = false;

			if (_pred(first, last, pred, depth))
			{
				_true(first, last, pred, depth);
				result = true;
			}
			else
			{
				_false(first, last, pred, depth);
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
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator first, Iterator last, Predicate pred, int depth = 0)
		{
			bool result = false;

			if (_pred(first, last, pred, depth))
			{
				_true(first, last, pred, depth);
				result = true;
			}

			_next(first, last, pred, depth);

			return result;

		}

	private:
		FilterPredicate _pred;
		TrueFilter _true;
		NextFilter _next;
	};



}