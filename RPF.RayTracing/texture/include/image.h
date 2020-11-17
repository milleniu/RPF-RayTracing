#pragma once
#ifndef RPF_RAYTRACING_TEXTURE_IMAGE_H_
#define RPF_RAYTRACING_TEXTURE_IMAGE_H_

#include "core/include/texture.h"

#include <boost/gil.hpp>

namespace ray_tracing
{
	namespace texture
	{
		class image final : public core::texture
		{
		public:
			image() = default;
			explicit image(const std::string& filename);

			color value(float u, float v, const point3& p) const override;

		private:
			boost::gil::rgb8_image_t data_{};
		};
	}
}

#endif
