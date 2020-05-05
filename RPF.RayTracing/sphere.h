#pragma once
#ifndef RPF_RAYTRACING_SPHERE_H
#define RPF_RAYTRACING_SPHERE_H

#include "hittable.h"
#include <utility>

namespace ray_tracing
{
	namespace hittable
	{
		class sphere final : public core::hittable_base
		{
		public:
			sphere() : center({}), radius(0.F) {}
			sphere(const point3 center, const float radius, std::shared_ptr<core::material_base> material)
				: center(center), radius(radius), material(std::move(material)) {}

			bool hit(const core::ray& r, float t_min, float t_max, core::hit_record& record) const override;
	
			point3 center;
			float radius;
			std::shared_ptr<core::material_base> material;
		};
	}
}

#endif
