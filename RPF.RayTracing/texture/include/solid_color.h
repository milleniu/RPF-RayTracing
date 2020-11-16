#pragma once
#ifndef RPF_RAYTRACING_TEXTURE_SOLID_COLOR_H
#define RPF_RAYTRACING_TEXTURE_SOLID_COLOR_H

#include "core/include/texture.h"

namespace ray_tracing
{
	namespace texture
	{
		class solid_color final : public core::texture
		{
		public:
			solid_color() = default;
			explicit solid_color(const color c) : color_value_(c) {}
			explicit solid_color(const float red, const float green, const float blue) : solid_color(color{ red, green, blue }) {}

			color value(float u, float v, const point3& p) const override;

		private:
			color color_value_{};
		};
	}
}

#endif
