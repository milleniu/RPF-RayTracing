#pragma once
#ifndef RPF_RAYTRACING_CORE_HITTABLE_H
#define RPF_RAYTRACING_CORE_HITTABLE_H

#include "core/include/ray.h"
#include "core/include/hit_record.h"
#include "core/include/aabb.h"

namespace ray_tracing
{
	namespace core
	{
		class hittable_base abstract
		{
		public:
			virtual ~hittable_base() {}
			
			virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
			virtual bool bbox(float t0, float t1, aabb& computed_bbox) const = 0;
		};
	}
}

#endif
