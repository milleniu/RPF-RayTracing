#pragma once
#ifndef RPF_RAYTRACING_MATERIAL_DIELECTRIC_H
#define RPF_RAYTRACING_MATERIAL_DIELECTRIC_H

#include "core/include/material.h"

namespace ray_tracing
{
	namespace material
	{
		class dielectric final : public core::material_base
		{
		public:
			explicit dielectric(float refractive_index);

			bool scatter
			(
				const core::ray& r,
				const core::hit_record& record,
				color& attenuation,
				core::ray& scattered
			) const override;

		private:
			float refractive_index_;
		};
	}
}

#endif
