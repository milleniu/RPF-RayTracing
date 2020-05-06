#pragma once
#ifndef RPF_RAYTRACING_METAL_H
#define RPF_RAYTRACING_METAL_H

#include "material.h"
#include "random.h"

namespace ray_tracing
{
	namespace material
	{
		class metal final : public core::material_base
		{
		public:
			explicit metal(const color& a, const float fuzz) : albedo(a), fuzz(fuzz < 1 && fuzz >= 0 ? fuzz : 1) {}
			
			bool scatter(const core::ray& r, const core::hit_record& record, color& attenuation, core::ray& scattered) const override;
			
			color albedo;
			float fuzz;
		};
	}
}

#endif
