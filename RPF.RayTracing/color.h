#pragma once
#ifndef RPF_RAYTRACING_COLOR_H
#define RPF_RAYTRACING_COLOR_H

#include "common.h"
#include "hittable.h"
#include "random.h"
#include "ray.h"
#include "camera.h"

#include <iostream>

namespace ray_tracing
{
	namespace core
	{
		inline color evaluate_ray_color(const ray& r, const hittable::hittable_base& world, const int depth, const diffuse_mode diffuse_mode)
		{
			hittable::hit_record record;

			if (depth <= 0) return color{ 0.F, 0.F, 0.F };

			if (world.hit(r, 0.001F, boost::math::tools::max_value<float>(), record))
			{
				vector3 target;
				switch (diffuse_mode)
				{
				case diffuse_mode::lambertian:
					target = record.position + record.normal + random_unit_vector();
					break;
					
				case diffuse_mode::hemisphere:
					target = record.position + random_in_hemisphere(record.normal);
					break;
				}
				return 0.5F * evaluate_ray_color(ray(record.position, target - record.position), world, depth - 1, diffuse_mode);
			}

			const auto unit_direction = unit_vector(r.direction());
			const auto t = 0.5F * (unit_direction.a[1] + 1.F);
			return color{ 1.F, 1.F, 1.F } *(1.F - t) + color{ 0.5F, 0.7F, 1.F } *t;
		}
		
		inline void write_color_to(std::ostream& out, const color pixel_color)
		{
			out << static_cast<int>(256 * clamp(boost::qvm::sqrt(pixel_color.a[0]), 0.F, 0.999F)) << ' '
				<< static_cast<int>(256 * clamp(boost::qvm::sqrt(pixel_color.a[1]), 0.F, 0.999F)) << ' '
				<< static_cast<int>(256 * clamp(boost::qvm::sqrt(pixel_color.a[2]), 0.F, 0.999F)) << '\n';
		}
	}
}

#endif
