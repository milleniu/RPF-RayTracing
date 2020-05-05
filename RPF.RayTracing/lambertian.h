#pragma once
#ifndef RAY_TRACING_LAMBERTIAN_H
#define RAY_TRACING_LAMBERTIAN_H

#include "material.h"
#include "random.h"

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
