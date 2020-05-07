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
				const float aspect_ratio,
				const float aperture,
				const float focus_distance
			)
			{
				origin_ = position;
				lens_radius_ = aperture / 2.F;

				const auto theta = degrees_to_radians(field_of_view);
				const auto half_height = boost::qvm::tan(theta / 2);
				const auto half_width = aspect_ratio * half_height;

				const auto vector_up = vector3{0.F, 1.F, 0.F};
				w_ = normalized(position - target);
				u_ = normalized(cross(vector_up, w_));
				v_ = cross(w_, u_);

				viewport_origin_ = origin_
					- half_width * focus_distance * u_
					- half_height * focus_distance * v_
					- focus_distance * w_;

				viewport_width_ = 2 * half_width * focus_distance * u_;
				viewport_height_ = 2 * half_height * focus_distance * v_;
			}

			ray get_ray(const float s, const float t) const
			{
				const auto random_in_disk = lens_radius_ * random_vector_in_disk();
				const auto offset = u_ * random_in_disk.a[0] + v_ * random_in_disk.a[1];

				return
				{
					origin_ + offset,
					viewport_origin_ + s * viewport_width_ + t * viewport_height_ - origin_ - offset
				};
			}

		private:
			point3 origin_;
			vector3 viewport_width_;
			vector3 viewport_height_;
			point3 viewport_origin_;
			vector3 u_;
			vector3 v_;
			vector3 w_;
			float lens_radius_;
		};
	}
}

#endif
