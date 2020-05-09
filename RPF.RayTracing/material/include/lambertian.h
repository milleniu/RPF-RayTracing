#pragma once
#ifndef RPF_RAYTRACING_MATERIAL_LAMBERTIAN_H
#define RPF_RAYTRACING_MATERIAL_LAMBERTIAN_H

#include "core/include/material.h"

namespace ray_tracing
{
	namespace material
	{
		class lambertian final : public core::material_base
		{
		public:
			explicit lambertian(const color& a): albedo(a) {}

			bool scatter(const core::ray& r, const core::hit_record& record, color& attenuation, core::ray& scattered) const override;

			color albedo;
		};
	}
	
}

#endif
