#pragma once
#ifndef RPF_RAYTRACING_HITTABLE_SPHERE_H
#define RPF_RAYTRACING_HITTABLE_SPHERE_H

#include "core/include/hittable.h"

namespace ray_tracing
{
	namespace hittable
	{
		class sphere final : public core::hittable
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
			bool bbox(float t0, float t1, core::aabb& computed_bbox) const override;

		private:
			point3 center_{};
			float radius_{};
			std::shared_ptr<core::material_base> material_{};

			static void get_sphere_uv(const point3& p, float& u, float& v)
			{
				const auto theta = boost::qvm::acos(-p.a[1]);
				const auto phi = boost::qvm::atan2(-p.a[2], p.a[0]) + boost::math::constants::pi<float>();

				u = phi / (2 * boost::math::constants::pi<float>());
				v = theta / boost::math::constants::pi<float>();
			}
		};
	}
}

#endif
