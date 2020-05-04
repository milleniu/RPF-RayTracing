#pragma once

#include "vector3.h"

class ray
{
public:
	ray() = default;

	ray(const point3& origin, const vector3& direction)
		: origin_(origin), direction_(direction) {}

	point3 origin() const { return origin_; }
	vector3 direction() const { return direction_; }

	point3 evaluate(const float t) const
	{
		return origin_ + direction_ * t;
	}

private:
	point3 origin_;
	vector3 direction_;
};
