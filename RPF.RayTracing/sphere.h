#pragma once
#ifndef RPF_RAYTRACING_SPHERE_H
#define RPF_RAYTRACING_SPHERE_H

#include "hittable.h"

namespace ray_tracing
{
	namespace hittable
	{
		class sphere final : public hittable_base
		{
		public:
			sphere() : center({}), radius(0.F) {}
			sphere(const point3 center, const float radius)
				: center(center), radius(radius) {}

			bool hit(const core::ray& r, float t_min, float t_max, hit_record& record) const override;
	
			point3 center;
			float radius;
		};
	}
}

#endif
