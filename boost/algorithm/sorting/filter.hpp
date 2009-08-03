
#pragma once

namespace boost
{

	template <typename FilterPredicate, typename TrueFilter, typename FalseFilter>
	struct sort_filter
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


}