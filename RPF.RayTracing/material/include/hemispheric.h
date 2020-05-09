#pragma once
#ifndef RPF_RAYTRACING_MATERIAL_HEMISPHERIC_H
#define RPF_RAYTRACING_MATERIAL_HEMISPHERIC_H

#include "core/include/material.h"

namespace ray_tracing
{
	namespace material
	{
		class hemispheric final : public core::material_base
		{
		public:
			explicit hemispheric(const color& a);

			bool scatter
			(
				const core::ray& r,
				const core::hit_record& record,
				color& attenuation,
				core::ray& scattered
			) const override;

		private:
			color albedo_;
		};
	}
}

#endif
