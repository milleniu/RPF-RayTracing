#pragma once
#ifndef RPF_RAYTRACING_HITTABLE_MOVING_SPHERE_H
#define RPF_RAYTRACING_HITTABLE_MOVING_SPHERE_H

#include "core/include/hittable.h"
#include <utility>

namespace ray_tracing
{
	namespace hittable
	{
		class moving_sphere final : public core::hittable_base
		{
		public:
			moving_sphere() = default;

			moving_sphere
			(
				const point3 origin,
				const point3 target,
				const float movement_start,
				const float movement_end,
				const float radius,
				std::shared_ptr<core::material_base> material
			) : origin(origin), target(target),
			    movement_start(movement_start), movement_end(movement_end),
			    radius(radius), material(std::move(material)) {}

			bool hit(const core::ray& r, float t_min, float t_max, core::hit_record& record) const override;

			point3 get_center(float t) const;

			point3 origin, target;
			float movement_start, movement_end;
			float radius;
			std::shared_ptr<core::material_base> material;
		};
	}
}

#endif
