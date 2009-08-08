
#pragma once

#include <functional>

#include <boost/algorithm/sorting/flex_tags.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>

#include <boost/algorithm/sorting/detail/insert_sort_core.hpp>

namespace boost
{
	
	typedef detail::default_predicate<detail::insert_sort_core, std::less> insert_sort;

}