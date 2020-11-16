#pragma once
#ifndef RPF_RAYTRACING_HITTABLE_LIST_H
#define RPF_RAYTRACING_HITTABLE_LIST_H

#include "core/include/hittable.h"
#include <memory>
#include <vector>

namespace ray_tracing
{
	namespace hittable
	{
		class hittable_list final : public core::hittable
		{
		public:
			hittable_list() = default;

			explicit hittable_list(const std::shared_ptr<hittable>& hittable);

			void add(const std::shared_ptr<hittable>& hittable);
			void clear();

			bool hit(const core::ray& r, float t_min, float t_max, core::hit_record& record) const override;
			bool bbox(float t0, float t1, core::aabb& computed_bbox) const override;

		private:
			std::vector<std::shared_ptr<hittable>> hittable_vector_;

		public:
			std::vector<std::shared_ptr<hittable>>& hittable_vector() { return hittable_vector_; }
		};
	}
}

#endif
