#pragma once
#ifndef RPF_RAYTRACING_CORE_AABB_H
#define RPF_RAYTRACING_CORE_AABB_H

#include "core/include/common.h"
#include "core/include/ray.h"

namespace ray_tracing
{
	namespace core
	{
		class aabb
		{
		public:
			aabb() = default;

			aabb(const point3& a, const point3& b);

			static aabb bbox(aabb a, aabb b);
			
			bool hit(const ray& r, float t_min, float t_max) const;

		private:
			point3 min_;
			point3 max_;

		public:
			point3 min() const { return min_; }
			point3 max() const { return max_; }
		};
	}
}

#endif
