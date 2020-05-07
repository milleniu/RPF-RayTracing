#pragma once
#ifndef RPF_RAYTRACING_COMMON_H
#define RPF_RAYTRACING_COMMON_H

#include <boost/math/constants/constants.hpp>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations.hpp>

namespace ray_tracing
{
	using vector3 = boost::qvm::vec<float, 3>;
	using point3 = vector3;
	using color = vector3;

	inline vector3 operator*(const vector3& u, const vector3& v)
	{
		return {u.a[0] * v.a[0], u.a[1] * v.a[1], u.a[2] * v.a[2]};
	}

	inline vector3 reflect(const vector3& u, const vector3& n)
	{
		return u - 2 * dot(u, n) * n;
	}

	inline vector3 refract(const vector3 uv, const vector3& n, const float refraction_factor)
	{
		const auto cos_theta = fminf(dot(-uv, n), 1.F);
		const auto parallel_vector = refraction_factor * (uv + cos_theta * n);
		const auto perpendicular_vector = -boost::qvm::sqrt(1.F - mag_sqr(parallel_vector)) * n;
		return parallel_vector + perpendicular_vector;
	}

	template <class T>
	constexpr const T& clamp(const T& value, const T& min, const T& max)
	{
		assert(!(max < min));
		return value < min ? min : value > max ? max : value;
	}

	template <class T>
	constexpr const T& schlick_approximation(const T& cosine, const T& refractive_index)
	{
		const auto r0 = (1 - refractive_index) / (1 + refractive_index);
		const auto r0_sqr = r0 * r0;
		return r0_sqr + (1 - r0_sqr) * boost::qvm::pow<T>((1 - cosine), static_cast<T>(5));
	}

	template <class T>
	constexpr const T& degrees_to_radians(const T& degrees) {
		return degrees * boost::math::constants::pi<T>() / static_cast<T>(180);
	}
}

#endif
