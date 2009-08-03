
#pragma once

namespace boost
{

namespace detail
{

	// always returns true will call the next in stack
	struct sort_filter_pass
	{
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator, Iterator, Predicate, int) const
		{
			return false;
		}
	};

	// always returns false, will call the current sorter
	struct sort_filter_block
	{
		template <typename Iterator, typename Predicate>
		bool operator()(Iterator, Iterator, Predicate, int) const
		{
			return true;
		}
	};


}

}