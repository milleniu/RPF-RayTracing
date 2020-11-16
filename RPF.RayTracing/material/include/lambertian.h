#pragma once
#ifndef RPF_RAYTRACING_MATERIAL_LAMBERTIAN_H
#define RPF_RAYTRACING_MATERIAL_LAMBERTIAN_H

#include "core/include/material.h"
#include "core/include/texture.h"

namespace ray_tracing
{
	namespace material
	{
		class lambertian final : public core::material_base
		{
		public:
			explicit lambertian(const color& a);
			explicit lambertian(std::shared_ptr<core::texture> a);

			bool scatter
			(
				const core::ray& r,
				const core::hit_record& record,
				color& attenuation,
				core::ray& scattered
			) const override;
			
		private:
			std::shared_ptr<core::texture> albedo_;
		};
	}
	
}

#endif
