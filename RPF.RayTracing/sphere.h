#pragma once

#include "hittable.h"
#include "vector3.h"
#include "ray.h"

class sphere final : public hittable
{
public:
	sphere() : radius(0.F) {}
	sphere(const point3 center, const float radius)
		: center(center), radius(radius) {}

	bool hit(const ray& r, float t_min, float t_max, hit_record& record) const override;
	
	point3 center;
	float radius;
};
