#pragma once
#ifndef RPF_RAYTRACING_HITTABLE_H
#define RPF_RAYTRACING_HITTABLE_H

#include "ray.h"

namespace ray_tracing
{
	namespace core
	{
		class material_base;
		
		struct hit_record
		{
			float t{};
			point3 position{};
			vector3 normal{};
			std::shared_ptr<material_base> material_ptr;
			bool front_face{};

			void set_face_normal(const ray&r, const vector3 outward_normal)
			{
				front_face = dot(r.direction(), outward_normal) < 0;
				normal = front_face ? outward_normal : -outward_normal;
			}
		};

		class hittable_base abstract
		{
		public:
			virtual ~hittable_base() {}
			virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
		};
	}
}

#endif
