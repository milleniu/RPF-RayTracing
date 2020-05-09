#pragma once
#ifndef RPF_RAYTRACING_CORE_RAY_H
#define RPF_RAYTRACING_CORE_RAY_H

#include "core/include/common.h"

namespace ray_tracing
{
	namespace core
	{
		class ray
		{
		public:
			ray() = default;

			ray(const point3& origin, const vector3& direction, float time = 0.F);
			
			point3 evaluate(float t) const;

		private:
			point3 origin_;
			vector3 direction_;
			float time_;

		public:
			point3 origin() const { return origin_; }
			vector3 direction() const { return direction_; }
			float time() const { return time_; }
		};
	}
}

#endif
