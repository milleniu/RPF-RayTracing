#pragma once
#ifndef RPF_RAYTRACING_COLOR_H
#define RPF_RAYTRACING_COLOR_H

#include "common.h"

#include <iostream>

namespace ray_tracing
{
	namespace core
	{
		inline void write_to(std::ostream& out, const color pixel_color)
		{
			out << static_cast<int>(256 * clamp(pixel_color.a[0], 0.F, 0.999F)) << ' '
				<< static_cast<int>(256 * clamp(pixel_color.a[1], 0.F, 0.999F)) << ' '
				<< static_cast<int>(256 * clamp(pixel_color.a[2], 0.F, 0.999F)) << '\n';
		}
	}
}

#endif
