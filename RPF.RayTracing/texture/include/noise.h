#pragma once
#ifndef RPF_RAYTRACING_TEXTURE_NOISE_H
#define RPF_RAYTRACING_TEXTURE_NOISE_H

#include "core/include/perlin.h"
#include "core/include/texture.h"

namespace ray_tracing
{
	namespace texture
	{
		class noise final : public core::texture
		{
		public:
			noise() = default;
			explicit noise(float sc);

			color value(float u, float v, const point3& p) const override;

		private:
			core::perlin perlin_noise_;
			float scale_{};
		};
	}
}

#endif
