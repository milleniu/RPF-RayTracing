#pragma once
#ifndef RPF_RAYTRACING_HITTABLE_SPHERE_H
#define RPF_RAYTRACING_HITTABLE_SPHERE_H

#include "core/include/hittable.h"

namespace ray_tracing
{
	namespace hittable
	{
		class sphere final : public core::hittable_base
		{
		public:
			sphere() = default;

			sphere
			(
				point3 center,
				float radius,
				std::shared_ptr<core::material_base> material
			);

			bool hit(const core::ray& r, float t_min, float t_max, core::hit_record& record) const override;

		private:
			point3 center_;
			float radius_;
			std::shared_ptr<core::material_base> material_;
		};
	}
}

#endif
