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

			ray(const point3& origin, const vector3& direction, const float time = 0.F)
				: origin_(origin), direction_(direction), time_(time) {}

			point3 origin() const { return origin_; }
			vector3 direction() const { return direction_; }
			float time() const { return time_;  }

			point3 evaluate(const float t) const
			{
				return origin_ + t * direction_ ;
			}

		private:
			point3 origin_;
			vector3 direction_;
			float time_;
		};
	}
}

#endif
