#pragma once
#ifndef RPF_RAYTRACING_CORE_MATERIAL_H
#define RPF_RAYTRACING_CORE_MATERIAL_H

#include "core/include/ray.h"

namespace ray_tracing
{
	namespace core
	{
		struct hit_record;

		class material_base abstract {
		public:
			virtual ~material_base() {}
			virtual bool scatter(const ray& r, const hit_record& record, color& attenuation, ray& scattered) const = 0;
		};
	}
}

#endif