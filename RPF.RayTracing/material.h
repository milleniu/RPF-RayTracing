#pragma once
#ifndef RPF_RAYTRACING_MATERIAL_H
#define RPF_RAYTRACING_MATERIAL_H

#include "common.h"
#include "ray.h"
#include "hittable.h"

namespace ray_tracing
{
	namespace core
	{
		class material_base abstract {
		public:
			virtual ~material_base() {}
			virtual bool scatter(const ray& r, const hit_record& record, color& attenuation, ray& scattered) const = 0;
		};
	}
}

#endif