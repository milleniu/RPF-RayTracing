#pragma once
#ifndef RPF_RAYTRACING_CORE_TEXTURE_H
#define RPF_RAYTRACING_CORE_TEXTURE_H

#include "core/include/color.h"

namespace ray_tracing
{
	namespace core
	{
		class texture abstract
		{
		public:
			virtual ~texture() {}

			virtual color value(float u, float v, const point3& p) const = 0;
		};
	}
	
}

#endif
