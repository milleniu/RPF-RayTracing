#include "texture/include/solid_color.h"

ray_tracing::color ray_tracing::texture::solid_color::value(float u, float v, const point3& p) const
{
	return color_value_;
}

