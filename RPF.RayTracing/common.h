#pragma once

#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations3.hpp>

using vector3 = boost::qvm::vec<float, 3>;
using point3 = vector3;
using color = vector3;

template<class T>
constexpr const T& clamp( const T& value, const T& min, const T& max )
{
	assert(!(max < min));
	return value < min ? min : value > max ? max : value;
}

inline vector3 unit_vector(const vector3 v)
{
	return v / 3;
}