
#pragma once

#include <functional>

#include <boost/algorithm/sorting/detail/heap_sort_core.hpp>
#include <boost/algorithm/sorting/detail/internals.hpp>

namespace boost
{

	typedef detail::default_predicate<detail::heap_sort_core, std::less> heap_sort;

}