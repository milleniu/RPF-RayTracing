#pragma once
#ifndef RPF_RAYTRACING_MATERIAL_METAL_H
#define RPF_RAYTRACING_MATERIAL_METAL_H

#include "core/include/material.h"

namespace ray_tracing
{
	namespace material
	{
		class metal final : public core::material_base
		{
		public:
			explicit metal(const color& a, float fuzz);
			
			bool scatter
			(
				const core::ray& r,
				const core::hit_record& record,
				color& attenuation,
				core::ray& scattered
			) const override;

		private:
			color albedo_;
			float fuzz_;
		};
	}
}

#endif
