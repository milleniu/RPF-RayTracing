#pragma once
#ifndef RPF_RAYTRACING_CAMERA_H
#define RPF_RAYTRACING_CAMERA_H

#include "common.h"
#include "ray.h"

namespace ray_tracing
{
	namespace core
	{
		class camera
		{
		public:
			camera
			(
				const point3 origin,
				const vector3 viewport_width,
				const vector3 viewport_height,
				const vector3 viewport_depth
			) :
				origin_(origin),
				viewport_width_(viewport_width),
				viewport_height_(viewport_height),
				viewport_origin_({
					origin.a[0] - viewport_width_.a[0] / 2,
					origin.a[1] - viewport_height_.a[1] / 2,
					origin.a[2] - viewport_depth.a[2]
				}) { }

			ray get_ray(const float u, const float v) const
			{
				return { origin_, viewport_origin_ + u * viewport_width_ + v * viewport_height_ - origin_ };
			}

		private:
			point3 origin_;
			vector3 viewport_width_;
			vector3 viewport_height_;
			point3 viewport_origin_;
		};
	}
}

#endif
