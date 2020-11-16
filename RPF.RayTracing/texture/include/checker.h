#pragma once
#ifndef RPF_RAYTRACING_TEXTURE_CHECKER_H
#define RPF_RAYTRACING_TEXTURE_CHECKER_H

#include "core/include/color.h"
#include "core/include/texture.h"

namespace ray_tracing
{
	namespace texture
	{
		class checker final : public core::texture
		{
		public:
			checker() = default;
			explicit checker(const std::shared_ptr<texture>& even, const std::shared_ptr<texture>& odd);
			explicit checker(color c1, color c2);

			color value(float u, float v, const point3& p) const override;

		private:
			std::shared_ptr<texture> even_{};
			std::shared_ptr<texture> odd_{};
		};
	}
}

#endif
