#pragma once
#ifndef RPF_RAYTRACING_HITTABLE_MOVING_SPHERE_H
#define RPF_RAYTRACING_HITTABLE_MOVING_SPHERE_H

#include "core/include/hittable.h"

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
				point3 origin,
				point3 target,
				float movement_start,
				float movement_end,
				float radius,
				std::shared_ptr<core::material_base> material
			);

			bool hit(const core::ray& r, float t_min, float t_max, core::hit_record& record) const override;
			bool bbox(float t0, float t1, core::aabb& computed_bbox) const override;

			point3 get_center(float t) const;

		private:
			point3 origin_;
			point3 target_;
			float movement_start_;
			float movement_end_;
			float radius_;
			std::shared_ptr<core::material_base> material_;
		};
	}
}

#endif
