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
				const point3 position,
				const point3 target,
				const float field_of_view,
				const float aspect_ratio
			)
			{
				origin_ = position;

				const auto theta = degrees_to_radians(field_of_view);
				const auto half_height = boost::qvm::tan(theta / 2);
				const auto half_width = aspect_ratio * half_height;

				const auto vector_up = vector3{ 0.F, 1.F, 0.F };
				const auto w = normalized(position - target);
				const auto u = normalized(cross(vector_up, w));
				const auto v = cross(w, u);
				
				viewport_origin_ = origin_ - half_width * u - half_height * v - w;
				viewport_width_ = 2 * half_width * u;
				viewport_height_ = 2 * half_height * v;
			}
			
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
