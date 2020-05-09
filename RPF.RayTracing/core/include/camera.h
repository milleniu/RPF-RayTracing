#pragma once
#ifndef RPF_RAYTRACING_CORE_CAMERA_H
#define RPF_RAYTRACING_CORE_CAMERA_H

#include "core/include/common.h"
#include "core/include/ray.h"

namespace ray_tracing
{
	namespace core
	{
		class camera
		{
		public:
			camera
			(
				point3 position,
				point3 target,
				float field_of_view,
				float aspect_ratio,
				float aperture,
				float focus_distance
			);

			ray get_ray(float s, float t, float time) const;

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
