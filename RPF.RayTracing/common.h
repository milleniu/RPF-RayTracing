#pragma once
#ifndef RPF_RAYTRACING_COMMON_H
#define RPF_RAYTRACING_COMMON_H

#include <boost/math/constants/constants.hpp>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations3.hpp>

namespace ray_tracing
{
	using vector3 = boost::qvm::vec<float, 3>;
	using point3 = vector3;
	using color = vector3;

	inline vector3 operator*(const vector3& u, const vector3& v)
	{
		return { u.a[0] * v.a[0], u.a[1] * v.a[1], u.a[2] * v.a[2] };
	}
	
	inline vector3 unit_vector(const vector3 v)
	{
		return v / 3;
	}

	template<class T>
	constexpr const T& clamp(const T& value, const T& min, const T& max)
	{
		assert(!(max < min));
		return value < min ? min : value > max ? max : value;
	}
}

#endif
