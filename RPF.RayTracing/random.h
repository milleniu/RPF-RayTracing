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

	inline vector3 random_vector_in_disk()
	{
		while (true)
		{
			const auto p = vector3{ random_float(-1.F, 1.F), random_float(-1.F, 1.F), 0 };
			if (mag_sqr(p) >= 1) continue;
			return p;
		}
	}

	inline vector3 random_in_hemisphere(const vector3& normal)
	{
		const auto in_unit_sphere = random_vector_in_unit_sphere();
		if (dot(in_unit_sphere, normal) > 0.F)
			return in_unit_sphere;
		else
			return -in_unit_sphere;
	}

	inline vector3 random_unit_vector()
	{
		const auto a = random_float(0, boost::math::constants::two_pi<float>());
		const auto z = random_float(-1.F, 1.F);
		const auto r = boost::qvm::sqrt(1 - z * z);
		return {r * cosf(a), r * sinf(a), z};
	}
}


#endif
