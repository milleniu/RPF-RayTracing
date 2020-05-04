#pragma once
#ifndef RPF_RAYTRACING_RANDOM_H
#define RPF_RAYTRACING_RANDOM_H

#include "common.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

namespace ray_tracing
{
	namespace detail
	{
		static boost::random::mt19937 rng;
	}

	inline float random_float()
	{
		return boost::random::uniform_real_distribution<float>()(detail::rng);
	}

	inline float random_float(const float min, const float max)
	{
		return boost::random::uniform_real_distribution<float>(min, max)(detail::rng);
	}

	inline vector3 random_vector()
	{
		return vector3
		{
			random_float(),
			random_float(),
			random_float()
		};
	}

	inline vector3 random_vector(const float min, const float max)
	{
		return vector3
		{
			random_float(min, max),
			random_float(min, max),
			random_float(min, max)
		};
	}

	inline vector3 random_vector_in_unit_sphere()
	{
		while (true)
		{
			const auto p = random_vector(-1.F, 1.F);
			if (mag_sqr(p) >= 1) continue;
			return p;
		}
	}
}


#endif
