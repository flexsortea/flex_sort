
#pragma once

#include <iterator>

namespace boost
{

	struct sorter_tag {};

	// this means the sorter is recursive
	struct recursive_sorter_tag : virtual sorter_tag {};

	// this means that a random iterator is required (or more appropriate)
	struct random_iterator_sorter_tag : virtual sorter_tag, std::random_access_iterator_tag
	{
	};

	// this means that a bidirectional iterator is required (or more appropriate)
	struct bidirectional_iterator_sorter_tag : virtual sorter_tag, std::bidirectional_iterator_tag
	{
	};

	// this means that a forward iterator is required (or more appropriate)
	struct forward_iterator_sorter_tag : virtual sorter_tag , std::forward_iterator_tag
	{
	};

}