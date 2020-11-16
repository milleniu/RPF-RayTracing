#pragma once
#ifndef	RPF_RAYTRACING_HITTABLE_BOUNDING_VOLUME_HIERARCHY_H
#define RPF_RAYTRACING_HITTABLE_BOUNDING_VOLUME_HIERARCHY_H

#include "hittable/include/hittable_list.h"
#include <iostream>

namespace ray_tracing
{
	namespace hittable
	{
		namespace detail
		{
			inline bool bbox_comparison
			(
				const std::shared_ptr<core::hittable>& a,
				const std::shared_ptr<core::hittable>& b,
				const int axis
			)
			{
				core::aabb bbox_a, bbox_b; // NOLINT(cppcoreguidelines-pro-type-member-init)

				if (!a->bbox(0.F, 0.F, bbox_a) | !b->bbox(0.F, 0.F, bbox_b))
					std::cerr << "bounding_volume_hierarchy :: bbox_comparison :: no bounding box.\n";

				return bbox_a.min().a[axis] < bbox_b.min().a[axis];
			}

			inline bool bbox_x_comparison
			(
				const std::shared_ptr<core::hittable>& a,
				const std::shared_ptr<core::hittable>& b
			)
			{
				return bbox_comparison(a, b, 0);
			}

			inline bool bbox_y_comparison
			(
				const std::shared_ptr<core::hittable>& a,
				const std::shared_ptr<core::hittable>& b
			)
			{
				return bbox_comparison(a, b, 1);
			}

			inline bool bbox_z_comparison
			(
				const std::shared_ptr<core::hittable>& a,
				const std::shared_ptr<core::hittable>& b
			)
			{
				return bbox_comparison(a, b, 2);
			}
		}

		class bounding_volume_hierarchy final : public core::hittable
		{
		public:
			bounding_volume_hierarchy() = default;

			bounding_volume_hierarchy(hittable_list& list, float t0, float t1);

			bounding_volume_hierarchy
			(
				std::vector<std::shared_ptr<core::hittable>>& hittable_list,
				size_t start,
				size_t end,
				float t0,
				float t1
			);

			bool hit(const core::ray& r, float t_min, float t_max, core::hit_record& record) const override;
			bool bbox(float t0, float t1, core::aabb& computed_bbox) const override;

		private:
			std::shared_ptr<hittable> left_;
			std::shared_ptr<hittable> right_;
			core::aabb bbox_{};
		};
	}
}

#endif
