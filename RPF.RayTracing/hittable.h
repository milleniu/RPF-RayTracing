#pragma once

#include "ray.h"

struct hit_record
{
	float t{};
	point3 position;
	vector3 normal;
	bool front_face{};

	void set_face_normal(const ray&r, const vector3 outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
	
};

class hittable abstract
{
public:
	virtual ~hittable() {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
};
