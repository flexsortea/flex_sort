
#pragma once

#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost
{

	template <unsigned int SmallThreshold>
	struct sort_input_small_enough
	{

		sort_input_small_enough(void)
		{
			// doesn't make sense to have a threshold <= 2
			// would mean all collections are considered small
			// we could push this up to 3 but let's keep it very formal
			BOOST_STATIC_ASSERT((SmallThreshold > 2));
		}

		// note that the depth type is hardcoded to unsigned int
		// whereas the DistanceType depends on the collection and the platform
		template <typename DistanceType>
		bool operator()(DistanceType distance) const
		{
			// if this static assertion failed, somehow the distance is not an integer
			BOOST_STATIC_ASSERT((boost::is_convertible<DistanceType, boost::uint64_t>::type));

			// if we had a size of 2^32 + 1, and SmallThreshold were a boost::uint32_t
			// this would incorrectly return true
			return static_cast<boost::uint64_t>(distance) < static_cast<boost::uint64_t>(SmallThreshold);
		}

	};

	template <unsigned int DepthThreshold>
	struct sort_rec_too_deep
	{

		sort_rec_too_deep(void)
		{
			// we allow at least one call, don't we?
			BOOST_STATIC_ASSERT((DepthThreshold > 1));
		}

		// note that the depth type is hardcoded to unsigned int
		// whereas the DistanceType depends on the collection and the platform
		template <typename DistanceType>
		bool operator()(unsigned int depth) const
		{
			return depth >= DepthThreshold;
		}

	};

}