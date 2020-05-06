#pragma once
#ifndef RPF_RAYTRACING_DIELECTRIC_H
#define RPF_RAYTRACING_DIELECTRIC_H

#include "material.h"
#include "random.h"

namespace ray_tracing
{
	namespace material
	{
		class dielectric final : public core::material_base
		{
		public:
			explicit dielectric(const float refractive_index) : refractive_index(refractive_index) {}

			bool scatter(const core::ray& r, const core::hit_record& record, color& attenuation, core::ray& scattered) const override;

			float refractive_index;
		};
	}
}

#endif
