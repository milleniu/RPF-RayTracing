#pragma once
#ifndef RPF_RAYTRACING_CORE_COLOR_H
#define RPF_RAYTRACING_CORE_COLOR_H

#include "core/include/hittable.h"
#include "core/include/ray.h"
#include "core/include/material.h"

#include <iostream>

namespace ray_tracing
{
	namespace core
	{
		inline color evaluate_ray_color(const ray& r, const hittable& world, const int depth)
		{
			hit_record record;

			if (depth <= 0) return {0.F, 0.F, 0.F};

			if (world.hit(r, 0.001F, boost::math::tools::max_value<float>(), record))
			{
				ray scattered{};
				color attenuation;
				if (record.material_ptr->scatter(r, record, attenuation, scattered))
				{
					return attenuation * evaluate_ray_color(scattered, world, depth - 1);
				}
				return {0.F, 0.F, 0.F};
			}

			const auto unit_direction = normalized(r.direction());
			const auto t = 0.5F * (unit_direction.a[1] + 1.F);
			return color{1.F, 1.F, 1.F} * (1.F - t) + color{0.5F, 0.7F, 1.F} * t;
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
