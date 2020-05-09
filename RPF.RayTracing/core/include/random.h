#pragma once
#ifndef RPF_RAYTRACING_CORE_RANDOM_H
#define RPF_RAYTRACING_CORE_RANDOM_H

#include "core/include/common.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

namespace ray_tracing
{
	namespace random
	{
		namespace detail
		{
			static boost::random::mt19937 rng;
		}

		template <class T>
		T random_value()
		{
			return boost::random::uniform_real_distribution<T>()(detail::rng);
		}

		template <class T>
		T random_value(const T min, const T max)
		{
			return boost::random::uniform_real_distribution<T>(min, max)(detail::rng);
		}

		inline vector3 random_vector()
		{
			return vector3
			{
				random_value<float>(),
				random_value<float>(),
				random_value<float>()
			};
		}

		inline vector3 random_vector(const float min, const float max)
		{
			return vector3
			{
				random_value<float>(min, max),
				random_value<float>(min, max),
				random_value<float>(min, max)
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
				const auto p = vector3{ random_value(-1.F, 1.F), random_value(-1.F, 1.F), 0 };
				if (mag_sqr(p) >= 1) continue;
				return p;
			}
		}

		inline vector3 random_in_hemisphere(const vector3& normal)
		{
			const auto in_unit_sphere = random_vector_in_unit_sphere();
			return dot(in_unit_sphere, normal) > 0.F ? in_unit_sphere : -in_unit_sphere;
		}

		inline vector3 random_unit_vector()
		{
			const auto a = random_value<float>(0, boost::math::constants::two_pi<float>());
			const auto z = random_value(-1.F, 1.F);
			const auto r = boost::qvm::sqrt(1 - z * z);
			return { r * boost::qvm::sin<float>(a), r * boost::qvm::sin<float>(a), z };
		}
	}
}

#endif
